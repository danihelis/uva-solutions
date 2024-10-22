/* 10943
 * How do you add?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100
#define MAX_K   100
#define DIGITS  1000000

int comb[MAX_N + 1][MAX_K];

/* Compute all combinations until MAX */
void compute_all() {
    int i, n, k;
    for (n = 0; n <= MAX_N; n++)
        comb[n][0] = 1;
    for (k = 1; k < MAX_K; k++)
        for (n = 0; n <= MAX_N; n++)
            for (i = 0; i <= n; i++)
                comb[n][k] = (comb[n][k] + comb[n - i][k - 1]) % DIGITS;
}

/* Main function */
int main() {
    int n, k;
    compute_all();
    while (scanf("%d %d", &n, &k) != EOF && n > 0)
        printf("%d\n", comb[n][k - 1]);
    return EXIT_SUCCESS;
}
