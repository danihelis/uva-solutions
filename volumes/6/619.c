/* 619
 * Numerically Speaking
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS      25
#define ALPHA_BASE      26
#define DECIMAL_BASE    1000
#define PADDING         22

typedef struct {
    int digit[MAX_DIGITS];
    int base, num_digits;
} bigint_t;


/* Multiply by a factor and sum another value */
void sum(bigint_t *n, bigint_t *a, int multi, int value, char increment) {
    int i, carry, sub;
    assert(a->base == n->base);
    for (i = 0, carry = value;
            i < a->num_digits || carry != 0 || (increment && i < n->num_digits);
            i++) {
        carry += i < a->num_digits ? a->digit[i] * multi : 0;
        if (increment) carry += i < n->num_digits ? n->digit[i] : 0;
        sub = 0;
        while (carry < 0) {
            carry += n->base, sub--;
        }
        n->digit[i] = carry % n->base;
        carry /= n->base;
        carry += sub;
    }
    assert(i <= MAX_DIGITS);
    n->num_digits = i;
    while (n->num_digits > 0 && n->digit[n->num_digits - 1] == 0) {
        n->num_digits--;
    }
}

int compare(bigint_t *a, bigint_t *b) {
    int i;
    if (a->num_digits != b->num_digits) return a->num_digits - b->num_digits;
    for (i = a->num_digits - 1; i >= 0; i--) {
        if (a->digit[i] != b->digit[i]) return a->digit[i] - b->digit[i];
    }
    return 0;
}


/* Print bigint according to its base */
void print_bigint(bigint_t *n) {
    int i;
    for (i = n->num_digits - 1; i >= 0; i--) {
        if (n->base == ALPHA_BASE) printf("%c", 'a' + n->digit[i]);
        else {
            printf(i == n->num_digits - 1 ? "%d%s" : "%03d%s",
                n->digit[i], i > 0 ? "," : "");
        }
    }
}


/* Main function */
int main() {
    char symbol;
    bigint_t alpha, decimal, quantity;
    int i;

    alpha.base = ALPHA_BASE, decimal.base = DECIMAL_BASE;
    quantity.base = ALPHA_BASE;

    while (scanf("%c", &symbol) == 1 && symbol != '*') {
        alpha.num_digits = decimal.num_digits = quantity.num_digits = 0;

        do {
            int digit = isdigit(symbol);
            int value = digit ? symbol - '0' : symbol - 'a' + 1;
            sum(&alpha, &alpha, digit ? 10 : ALPHA_BASE, value, 0);
            sum(&decimal, &decimal, digit ? 10 : ALPHA_BASE, value, 0);
        } while (scanf("%c", &symbol) == 1 && symbol != '\n');

        sum(&quantity, &quantity, 0, ALPHA_BASE, 0);
        sum(&alpha, &alpha, 0, -1, 1);
        while (compare(&alpha, &quantity) > 0) {
            sum(&alpha, &quantity, -1, 0, 1);
            sum(&quantity, &quantity, ALPHA_BASE, 0, 0);
        }

        for (; alpha.num_digits < quantity.num_digits - 1; alpha.num_digits++) {
            alpha.digit[alpha.num_digits] = 0;
        }

        print_bigint(&alpha);
        for (i = alpha.num_digits; i < PADDING; i++) {
            printf(" ");
        }
        print_bigint(&decimal);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
