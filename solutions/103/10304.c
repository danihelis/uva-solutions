/* 10304
 * Optimal Binary Search Tree
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       250
#define INFINITY    (1 << 30)

int frequency[MAX_N][MAX_N], cost[MAX_N][MAX_N];
int n;

/* Compute best cost using dynamic programming */
int smallest_cost() {
    int i, j, k, d;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            frequency[i][j] = frequency[i][j - 1] + frequency[j][j];
        }
    }
    for (d = 0; d < n; d++) {
        for (i = 0, j = d; j < n; i++, j++) {
            if (d == 0) cost[i][i] = 0;
            else {
                int val, smallest = INFINITY;
                for (k = i; k <= j; k++) {
                    val = (k == i ? 0 : cost[i][k - 1] + frequency[i][k - 1]) +
                          (k == j ? 0 : cost[k + 1][j] + frequency[k + 1][j]);
                    if (val < smallest) smallest = val;
                }
                cost[i][j] = smallest;
            }
        }
    }
    return cost[0][n - 1];
}

/* Main function */
int main() {
    int i;
    while (scanf("%d", &n) == 1) {
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &frequency[i][i]) == 1);
        }
        printf("%d\n", smallest_cost());
    }
    return EXIT_SUCCESS;
}
