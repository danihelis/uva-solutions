/* 10125
 * Sumsets
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define NUM_PARCELS 3

int set[MAX_N], n, used[NUM_PARCELS], highest;

/* Compare integers */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Find an element equal to sum of NUM_PARCELS */
void find_highest_sum(int index, int k, int sum) {
    if (k == NUM_PARCELS) {
        if (sum > highest && bsearch(&sum, set, n, sizeof (int), compare) != NULL) {
            for (index = 0; index < NUM_PARCELS; index++)
                if (used[index] == sum)
                    return;
            highest = sum;
        }
    }
    else
        for (; index <= n - NUM_PARCELS + k; index++) {
            used[k] = set[index];
            find_highest_sum(index + 1, k + 1, sum + set[index]);
        }
}

/* Main function */
int main() {
    while (scanf("%d", &n) == 1 && n > 0) {
        int i;
        for (i = 0; i < n; i++)
            assert(scanf("%d", &set[i]) == 1);
        qsort(set, n, sizeof (int), compare);
        highest = set[0] - 1;
        find_highest_sum(0, 0, 0);
        if (highest >= set[0])
            printf("%d\n", highest);
        else
            puts("no solution");
    }
    return EXIT_SUCCESS;
}
