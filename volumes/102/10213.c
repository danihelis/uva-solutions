/* 10213
 * How Many Pieces of Land ?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  20
#define BASE        10000
#define FORMAT      "%04d"

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

/* Set number */
void set(bigint_t *b, int value) {
    int i;
    for (i = 0; value > 0; i++, value /= BASE)
        b->digit[i] = value % BASE;
    b->size = i;
}

/* Sum with shift */
void sum(bigint_t *r, bigint_t *a, bigint_t *b, int shift, int factor) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->size || i - shift < b->size;
            i++) {
        carry += (i < a->size ? a->digit[i] : 0) + (i - shift >= 0 &&
                i - shift < b->size ? b->digit[i - shift] * factor : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->size = i;
}

/* Subtract (a must be greater than or equal to b) */
void subtract(bigint_t *r, bigint_t *a, bigint_t *b, int factor) {
    int i, deficit;
    for (i = 0, deficit = 0; i < a->size || i < b->size; i++) {
        int difference = (i < a->size ? a->digit[i] : 0) -
                (i < b->size ? b->digit[i] * factor : 0) - deficit;
        deficit = difference >= 0 ? 0 : (BASE - 1 - difference) / BASE;
        r->digit[i] = difference + deficit * BASE;
    }
    while (i > 0 && r->digit[i - 1] == 0)
        i--;
    r->size = i;
}

/* Multiply */
void multiply(bigint_t *r, bigint_t *a, bigint_t *b) {
    bigint_t parcel;
    int i;
    r->size = 0;
    for (i = 0; i < a->size; i++) {
        sum(&parcel, r, b, i, a->digit[i]);
        *r = parcel;
    }
}

/* Divide by a factor and return the reminder */
int divide(bigint_t *n, int factor) {
    int i, carry;
    for (i = n->size - 1, carry = 0; i >= 0; i--, carry *= BASE) {
        carry += n->digit[i];
        n->digit[i] = carry / factor;
        carry %= factor;
    }
    for (; n->size > 0 && n->digit[n->size - 1] == 0; n->size--)
        ;
    return carry;
}

/* Print */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->digit[n->size - 1]);
    for (i = n->size - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
    printf("\n");
}

/* Compute combination for N: (N^4 - 6·N^3 + 23·N^4 - 18·N)/24 + 1 */
void compute(bigint_t *r, int n) {
    bigint_t n1, n2, n3, n4, p;
    set(&n1, n);
    multiply(&n2, &n1, &n1);
    multiply(&n3, &n1, &n2);
    multiply(&n4, &n1, &n3);
    r->size = 0;
    sum(r, &n4, &n2, 0, 23);
    subtract(&p, r, &n3, 6);
    subtract(r, &p, &n1, 18);
    assert(divide(r, 24) == 0);
    p.digit[0] = 1, p.size = 1;
    sum(r, r, &p, 0, 1);
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int n;
        bigint_t value;
        assert(scanf("%d", &n) != EOF);
        compute(&value, n);
        print_bigint(&value);
    }
    return EXIT_SUCCESS;
}
