/* 10925
 * Krakovia
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE        10000
#define MAX_DIGITS  10
#define MAX_STRING  25

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t;


/* Read bigint */
void read_bigint(bigint_t *n) {
    char string[MAX_STRING], *c;
    int i;
    assert(scanf(" %s", string) != EOF);
    i = strlen(string); 
    n->num_digits = 0;
    do {
        i -= 4;
        c = string + (i < 0 ? 0 : i);
        sscanf(c, "%d", &n->digit[n->num_digits++]);
        *c = 0;
    } while (i > 0);
}

/* Sum two bigints */
void sum_bigint(bigint_t *r, bigint_t *a, bigint_t *b) {
    int i, carry;
    for (i = carry = 0; carry || i < a->num_digits || i < b->num_digits; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) + 
                 (i < b->num_digits ? b->digit[i] : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Divide bigint by an integer that is lesser than BASE */
void divide_bigint(bigint_t *r, bigint_t *n, int div) {
    int i, carry;
    for (i = n->num_digits - 1, carry = 0; i >= 0; i--) {
        carry = carry * BASE + n->digit[i];
        r->digit[i] = carry / div;
        carry %= div;
    }
    for (i = n->num_digits; i > 0 && r->digit[i - 1] == 0; i--)
        ;
    r->num_digits = i;
}

/* Print bigint */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->num_digits > 0 ? n->digit[n->num_digits - 1] : 0);
    for (i = n->num_digits - 2; i >= 0; i--) {
        printf("%04d", n->digit[i]);
    }
}

/* Main function */
int main() {
    bigint_t number, sum, result;
    int test = 0, n, div;
    while (scanf("%d %d", &n, &div) != EOF && n > 0) {
        int i;
        sum.num_digits = 0;
        for (i = 0; i < n; i++) {
            read_bigint(&number);
            sum_bigint(&sum, &sum, &number);
        }
        divide_bigint(&result, &sum, div);
        printf("Bill #%d costs ", ++test);
        print_bigint(&sum);
        printf(": each friend should pay ");
        print_bigint(&result);
        printf("\n\n");
    }
    return EXIT_SUCCESS;
}
