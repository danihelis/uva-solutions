/* 10041
 * Vito's Family
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NEIGHS      500
#define ABS_DIFF(x, y)  (x < y ? y - x : x - y)

/* Compare int */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, n, dist, house, neigh[MAX_NEIGHS];
        assert(scanf("%d", &n) != EOF);
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &neigh[i]) != EOF);
        }
        qsort(neigh, n, sizeof (int), compare);
        house = neigh[n / 2];
        for (i = 0, dist = 0; i < n; i++) {
            dist += ABS_DIFF(neigh[i], house);
        }
        printf("%d\n", dist);
    }
    return 0;
}
