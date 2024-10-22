/* 10721
 * Bar Codes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   50
#define MAX_K   50
#define MAX_M   50

long bars[MAX_M][MAX_K][MAX_N];
char computed[MAX_M];

/* Compute existing bars */
void compute(int m) {
    int i, n, k;
    for (n = 1; n <= MAX_N; n++)
        bars[m - 1][n - 1][0] = n <= m ? 1 : 0;
    for (k = 2; k <= MAX_K; k++)
        for (n = 1; n <= MAX_N; n++) {
            bars[m - 1][n - 1][k - 1] = 0;
            for (i = 1; i <= m && n - i >= k - 1; i++)
                bars[m - 1][n - 1][k - 1] += 
                        bars[m - 1][n - 1 - i][k - 2];
        }
    computed[m - 1] = 1;
}

/* Main function */
int main() {
    int n, k, m;
    memset(computed, 0, MAX_M);
    while (scanf("%d %d %d", &n, &k, &m) != EOF) {
        if (!computed[m - 1])
            compute(m);
        printf("%ld\n", bars[m - 1][n - 1][k - 1]);
    }
    return EXIT_SUCCESS;
}
