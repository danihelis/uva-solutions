/* 10198
 * Counting
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
#define MAX_DIGITS      120

#define MAX_N           1000

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

bigint_t table[MAX_N + 1];

/* Add scaled bigint */
void add(bigint_t *r, bigint_t *a, int scale) {
    int i, carry;
    for (i = carry = 0; carry > 0 || i < r->size || i < a->size; i++) {
        carry += (i < r->size ? r->digit[i] : 0) +
                (i < a->size ? a->digit[i] * scale : 0);
        assert(i < MAX_DIGITS);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->size = i;
}

/* Print bigint */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->digit[n->size - 1]);
    for (i = n->size - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
    puts("");
}

/* Compute table */
void compute_table() {
    int i, k;
    table[0].digit[0] = 1, table[0].size = 1;
    for (i = 1; i <= MAX_N; i++) {
        table[i].size = 0;
        for (k = 1; k <= 3; k++)
            if (i - k >= 0)
                add(&table[i], &table[i - k], k == 1 ? 2 : 1);
    }
}

/* Main function */
int main() {
    int n;
    compute_table();
    while (scanf("%d", &n) == 1)
        print_bigint(&table[n]);
    return EXIT_SUCCESS;
}
