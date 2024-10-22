/* 11470
 * Square Sums
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10

/* Main function */
int main() {
    int n, square[MAX_N][MAX_N], sum[MAX_N];
    int test = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        int i, j, k;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                assert(scanf("%d", &square[i][j]) == 1);
        for (k = 0; k < (n + 1) / 2; k++) {
            int low = (n - 1) / 2 - k, up = n / 2 + k;
            sum[k] = 0; 
            for (i = low; i <= up; i++)
                if (i == low || i == up)
                    for (j = low; j <= up; j++)
                        sum[k] += square[i][j];
                else
                    sum[k] += square[i][low] + square[i][up];
        }
        printf("Case %d:", ++test);
        for (k = (n - 1) / 2; k >= 0; k--)
            printf(" %d", sum[k]);
        puts("");           
    }
    return EXIT_SUCCESS;
}
