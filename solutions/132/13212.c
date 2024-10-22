/* 13212
 * How many inversions?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000000

int vector[MAX_N], swap[MAX_N];

/* Sort the vector and return the number of inversions */
long merge_sort(int start, int end) {
    int middle, i, j, k;
    long inversions;
    if (end - start <= 1) return 0;
    middle = (start + end) / 2;
    inversions = merge_sort(start, middle) + merge_sort(middle, end);
    for (i = start, j = middle, k = start; k < end; k++) {
        if (j == end || (i < middle && vector[i] <= vector[j])) {
            swap[k] = vector[i++];
        } else {
            swap[k] = vector[j++];
            inversions += (middle - i);
        }
    }
    for (k = start; k < end; k++) {
        vector[k] = swap[k];
    }
    return inversions;
}

/* Main function */
int main() {
    int n, i;
    while (scanf("%d", &n) == 1 && n > 0) {
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &vector[i]) == 1);
        }
        printf("%ld\n", merge_sort(0, n));
    }
    return EXIT_SUCCESS;
}
