/* 11389
 * The Bus Driver Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

int time[2][MAX_N];

/* Compare */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int n, d, r;
    while (scanf("%d %d %d", &n, &d, &r) != EOF && n > 0) {
        int i, k, penalty;
        for (k = 0; k < 2; k++) {
            for (i = 0; i < n; i++) 
                assert(scanf("%d", &time[k][i]) != EOF);
            qsort(time[k], n, sizeof (int), compare);
        }
        for (i = 0, penalty = 0; i < n; i++) {
            int sum = time[0][i] + time[1][n - i - 1];
            if (sum > d)
                penalty += (sum - d) * r;
        }
        printf("%d\n", penalty);
    }
    return EXIT_SUCCESS;
}
