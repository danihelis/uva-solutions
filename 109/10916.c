/* 10916
 * Factstone Benchmark
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Computed offline */
#if 0
#define WORD_SIZE   16
#define BASE        (1 << WORD_SIZE)
#define MAX_DIGITS  1000000
#define MAX_YEARS   21
#define START_SIZE  4

typedef struct {
    long digit[MAX_DIGITS], size;
} bigint_t;

int factstone[MAX_YEARS];

/* Scale up */
void scale(bigint_t *n, long scalar) {
    long i, carry;
    for (i = 0, carry = 0; carry > 0 || i < n->size; i++) {
        carry += (i < n->size ? n->digit[i] * scalar : 0);
        n->digit[i] = carry % BASE;
        carry /= BASE;
    }
    n->size = i;
}

/* Can hold */
int can_be_hold(bigint_t *n, long size) {
    if (size < WORD_SIZE)
        return n->size <= 1 && n->digit[0] <= (1 << size);
    return n->size <= size / WORD_SIZE;
}

/* Compute all factstones */
void compute_factstones() {
    bigint_t factorial;
    int year;
    long size, n;
    factorial.digit[0] = 1, factorial.size = 1;
    for (year = 0, n = 1, size = 4; year < MAX_YEARS; year++) {
        while (can_be_hold(&factorial, size)) {
            factstone[year] = n;
            scale(&factorial, ++n);
        }
        fprintf(stderr, "%d (%d) N=%ld SIZE=%ld\n", 
                year, (year + 196) * 10, n - 1, size);
        size *= 2;
    }
}

/* Main function */
int main() {
    int n;
    compute_factstones();
    while (scanf("%d", &n) != EOF && n > 0) {
        int index = n / 10 - 196;
        assert(index >= 0 && index < MAX_YEARS);
        printf("%d\n", factstone[index]);
    }
    return EXIT_SUCCESS;
}
#endif

#define MAX_YEARS   21
int factstone[MAX_YEARS] = {
    3,
    5,
    8,
    12,
    20,
    34,
    57,
    98,
    170,
    300,
    536,
    966,
    1754,
    3210,
    5910,
    10944,
    20366,
    38064,
    71421,
    134480,
    254016
};

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int index = n / 10 - 196;
        assert(index >= 0 && index < MAX_YEARS);
        printf("%d\n", factstone[index]);
    }
    return EXIT_SUCCESS;
}
