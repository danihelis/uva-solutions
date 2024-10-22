/* 11997
 * K Smallest Sums
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_K       750

typedef struct {
    int value[MAX_K], rank[MAX_K], lowest[MAX_K];
    int num_ranks, num_lowest;
} array_t;

array_t array[MAX_K];
int k;

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Get n-th lowest summation of arrays from index .. K */
int lowest_sum(int n, int index) {
    array_t *a = &array[index];
    int i, lowest, best_i;
    if (index == k - 1) return a->value[n];
    if (n < a->num_lowest) return a->lowest[n];
    assert(n == a->num_lowest);
    for (i = 0, lowest = best_i = -1; i <= a->num_ranks; i++) {
        int sum = a->value[i] + lowest_sum(a->rank[i], index + 1);
        if (lowest == -1 || sum < lowest) lowest = sum, best_i = i;
    }
    a->lowest[a->num_lowest++] = lowest;
    a->rank[best_i]++;
    if (best_i == a->num_ranks) a->num_ranks++;
    return lowest;
}

/* Main function */
int main() {
    int i, j;
    while (scanf("%d", &k) == 1) {
        for (i = 0; i < k; i++) {
            array_t *a = &array[i];
            a->num_ranks = a->num_lowest = 0;
            for (j = 0; j < k; j++) {
                assert(scanf("%d", &a->value[j]) == 1);
                a->rank[j] = 0;
            }
            qsort(a->value, k, sizeof (int), compare);
        }
        for (i = 0; i < k; i++) {
            printf("%d%c", lowest_sum(i, 0), i < k - 1 ? ' ' : '\n');
        }
    }
    return EXIT_SUCCESS;
}
