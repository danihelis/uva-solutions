/* 10007
 * Count the Trees
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE            10000
#define FORMAT          "%04d"
#define MAX_DIGITS      10000
#define MAX_N           300

typedef struct {
    int digit[MAX_DIGITS], num_digits;
} bigint_t;

bigint_t combination[MAX_N + 1];
bigint_t pascal[MAX_N][MAX_N];
int max_comb;

/* Init a bigint */
void init(bigint_t *n, int value) {
    n->digit[0] = value;
    n->num_digits = value > 0 ? 1 : 0;
}

/* Sum two bigints */
void sum(bigint_t *r, bigint_t *a, bigint_t *b, int shift, int scalar) {
    int i;
    long carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || 
            i < b->num_digits + shift; i++) {
        assert(i < MAX_DIGITS);
        carry += (i < a->num_digits ? a->digit[i] : 0) +
                (i >= shift && i < b->num_digits + shift ?
                        b->digit[i - shift] * scalar : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    while (i > 0 && r->digit[i - 1] == 0)
        i--;
    r->num_digits = i;
}

/* Multiply two bigints */
void multiply(bigint_t *r, bigint_t *a, bigint_t *b) {
    int i;
    init(r, 0);
    for (i = 0; i < a->num_digits; i++)
        sum(r, r, b, i, a->digit[i]);
}

/* Compute combination */
void compute(int n) {
    int i, k;
    bigint_t comb1, comb2;
    init(&combination[n], 0);
    for (i = 0; i < n; i++)
        if (i == 0 || i == n - 1)
            init(&pascal[i][n - 1], 1);
        else
            sum(&pascal[i][n - 1], &pascal[i - 1][n - 2], &pascal[i][n - 2], 
                    0, 1);
    for (i = 0, k = n % 2 == 0 ? n / 2 : n / 2 + 1; i < k; i++) {
        multiply(&comb1, &combination[i], &combination[n - i - 1]);
        multiply(&comb2, &comb1, &pascal[i][n - 1]);
        sum(&combination[n], &combination[n], &comb2, 0,  n *
                (i == n / 2 && n % 2 == 1 ? 1 : 2));
    }
}

/* Print a bigint */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->digit[n->num_digits - 1]);
    for (i = n->num_digits - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
    printf("\n");
}

/* Main function */
int main() {
    int n;
    init(&combination[0], 1);
    init(&pascal[0][0], 1);
    max_comb = 0;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (; max_comb < n; max_comb++)
            compute(max_comb + 1);
        print_bigint(&combination[n]);
    }
    return EXIT_SUCCESS;
}
