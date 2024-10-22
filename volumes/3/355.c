/* 355
 * The Bases Are Loaded
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100
#define MAX_DIGITS  (MAX_STRING)
#define MIN_BASE    2

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits, base;
} bigint_t, *bigint_p;

/* Set initial value of bigint */
void set_bigint(bigint_p n, int v, int b) {
    n->digit[0] = v;
    n->num_digits = 1;
    n->base = b;
}

/* Sum two bigints of same base */
void sum_bigint(bigint_p a, int m, bigint_p b, bigint_p c) {
    int i, carry;
    assert(a->base == b->base && a->base > 1);
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits; i++) {
        int sum = carry + (i < a->num_digits ? a->digit[i] : 0) +
            (i < b->num_digits ? m * b->digit[i] : 0);
        c->digit[i] = sum % a->base;
        carry = sum / a->base;
    }
    assert(i < MAX_DIGITS);
    c->base = a->base;
    c->num_digits = i;
}

/* Convert from one base into another */
void convert_base(bigint_p a, int base, bigint_p b) {
    bigint_t factor;
    int i;
    set_bigint(b, 0, base);
    for (i = 0; i < a->num_digits; i++) {
        if (i == 0) {
            set_bigint(&factor, 1, base);
        }
        else {
            bigint_t zero;
            set_bigint(&zero, 0, base);
            sum_bigint(&zero, a->base, &factor, &zero);
            factor = zero;
        }
        sum_bigint(b, a->digit[i], &factor, b);
    }
}

/* Convert char sequence into baseless bigint and return least base */
int to_bigint(char *sequence, bigint_p n) {
    int i, base;
    n->num_digits = strlen(sequence);
    n->base = 0;
    for (i = n->num_digits - 1, base = MIN_BASE; i >= 0; sequence++, i--) {
        n->digit[i] = (isdigit(*sequence) ? *sequence - '0' : *sequence - 'A' + 10);
        if (n->digit[i] >= base) {
            base = n->digit[i] + 1;
        }
    }
    return base;
}

/* Print bigint */
void print_bigint(bigint_p n) {
    int i;
    for (i = n->num_digits - 1; i >= 0; i--) {
        int v = n->digit[i];
        printf("%c", (v < 10 ? v + '0' : v - 10 + 'A'));
    }
    printf(" base %d\n", n->base);
}

/* Main function */
int main() {
    int base_in, base_out;
    bigint_t original, converted;
    char input[MAX_STRING];
    while (scanf("%d %d %s", &base_in, &base_out, input) != EOF) {
        if (to_bigint(input, &original) > base_in) {
            printf("%s is an illegal base %d number\n", input, base_in);
        }
        else {
            original.base = base_in;
            convert_base(&original, base_out, &converted);
            printf("%s base %d = ", input, base_in);
            print_bigint(&converted);
        }
    }
    return 0;
}
