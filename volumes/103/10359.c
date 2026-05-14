/* 10359
 * Tiling
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS      100
#define BASE            10000
#define FORMAT          "%04d"

#define MAX_N           250

typedef struct {
    int digits[MAX_DIGITS];
    int size;
} bigint_t;

bigint_t combinations[MAX_N + 1];

/* Sum two bigints: r = a + s·b */
void sum_bigint(bigint_t *r, bigint_t *a, bigint_t *b, int scalar) {
    int i, carry;
    for (i = carry = 0; carry || i < a->size || i < b->size; i++) {
        carry += (i < a->size ? a->digits[i] : 0) +
            (i < b->size ? b->digits[i] * scalar : 0);
        r->digits[i] = carry % BASE;
        carry /= BASE;
    }
    r->size = i;
}

/* Print bigint */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->size > 0 ? n->digits[n->size - 1] : 0);
    for (i = n->size - 2; i >= 0; i--) {
        printf(FORMAT, n->digits[i]);
    }
}

/* Compute all combinations */
void compute_combinations() {
    int i;

    combinations[0].size = 1, combinations[0].digits[0] = 1;
    combinations[1].size = 1, combinations[1].digits[0] = 1;

    for (i = 2; i <= MAX_N; i++) {
        sum_bigint(&combinations[i], &combinations[i - 1], &combinations[i - 2], 2);
    }
}


/* Main function */
int main() {
    int n;

    compute_combinations();

    while (scanf("%d", &n) == 1) {
        print_bigint(&combinations[n]);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
