/* 10303
 * How Many Trees?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES       1001
#define MAX_DIGITS      100
#define BIGINT_BASE     1000000000
#define BIGINT_PRINT    "%09d"

typedef struct {
    int digit[MAX_DIGITS];
    int size;
} bigint_t;

bigint_t comb[MAX_NODES];
int last_computed;

/* Set a initial value for bignumber */
void set_bigint(bigint_t *b, unsigned int value) {
    b->digit[0] = value;
    b->size = 1;
}

/* Sum two bignumbers */
void sum_bigint(bigint_t *c, bigint_t *a, bigint_t *b, long factor, int displace) {
    int i;
    long carry;
    for (i = 0, carry = 0; carry > 0 || i < a->size || i < (b->size + displace); i++) {
        long sum = (i < a->size ? a->digit[i] : 0) + 
            (i >= displace && i < (b->size + displace) ? b->digit[i - displace] * factor : 0) + 
            carry;
        c->digit[i] = sum % BIGINT_BASE;
        carry = sum / BIGINT_BASE;
    }
    c->size = i;
}

/* Multiply two bignumbers */
void multiply_bigint(bigint_t *c, bigint_t *a, bigint_t *b) {
    int i;
    set_bigint(c, 0);
    for (i = 0; i < b->size; i++) {
        if (b->digit[i] > 0) {
            sum_bigint(c, c, a, b->digit[i], i);
        }
    }
}

/* Print bignumber */
void print_bignumber(bigint_t *n) {
    int i;
    for (i = n->size - 1; i >= 0; i--) {
        printf((i == n->size - 1 ? "%d" : BIGINT_PRINT), n->digit[i]);
    }
}

/* Compute the possible number of combinations for a tree with N nodes */
void compute(int n) {
    int i;
    bigint_t term;
    set_bigint(&comb[n], 0);
    for (i = 0; i < n; i++) {
        multiply_bigint(&term, &comb[i], &comb[n - i - 1]);
        sum_bigint(&comb[n], &comb[n], &term, 1, 0);
    }
}

/* Main function */
int main() {
    int n;
    set_bigint(&comb[0], 1), last_computed = 1;
    while (scanf("%d", &n) != EOF) {
        if (n >= last_computed) {
            for (; last_computed <= n; last_computed++) {
                compute(last_computed);
            }
        }
        print_bignumber(&comb[n]);
        printf("\n");
    }
    return 0;
}
