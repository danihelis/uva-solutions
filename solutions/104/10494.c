/* 10494
 * If We Were a Child Again
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGIT   1000
#define MAX_STRING  1000000
#define DEC_BASE    1000000000
#define MAX_BASE    (1L << 31)

typedef struct {
    unsigned long digit[MAX_DIGIT], base;
    int size;
} bigint_t;

/* Shift and sum in any base */
void shift_and_sum(bigint_t *n, unsigned long shift, unsigned long value) {
    int i;
    unsigned long carry;
    for (i = 0, carry = value; carry > 0 || i < n->size; i++) {
        carry += (i < n->size ? n->digit[i] * shift : 0);
        n->digit[i] = carry % n->base;
        carry /= n->base;
    }
    n->size = i;
}

/* Read on base MAX_BASE */
void read_bigint(bigint_t *n) {
    char string[MAX_STRING], *d;
    n->size = 0, n->base = MAX_BASE;
    assert(scanf(" %s", string) == 1);
    for (d = string; *d != 0; d++)
        shift_and_sum(n, 10, *d - '0');
}

/* Divide bigint and convert base to DEC_BASE */
void divide_bigint(bigint_t *n, unsigned long div, bigint_t *q, 
        unsigned long *r) {
    int i;
    q->size = 0, q->base = DEC_BASE;
    for (i = n->size - 1, *r = 0; i >= 0; i--) {
        *r = (*r * n->base) + n->digit[i];
        shift_and_sum(q, n->base, *r / div);
        *r %= div;
    }
}

/* Print bigint in DEC_BASE */
void print_bigint(bigint_t *n) {
    if (n->size == 0)
        printf("0\n");
    else {
        int i;
        printf("%lu", n->digit[n->size - 1]);
        for (i = n->size - 2; i >= 0; i--)
            printf("%09lu", n->digit[i]);
        printf("\n");
    }
}

/* Main function */
int main() {
    while (!feof(stdin)) {
        bigint_t a, q;
        unsigned long b, r;
        char op;
        read_bigint(&a);
        assert(scanf(" %c %lu ", &op, &b) == 2);
        divide_bigint(&a, b, &q, &r);
        if (op == '%')
            printf("%lu\n", r);
        else
            print_bigint(&q);
    }
    return EXIT_SUCCESS;
}
