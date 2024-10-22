/* 11417
 * GCD
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   500

int table[MAX_N][MAX_N], sum[MAX_N];

/* Greatest common divisor */
int gcd(int a, int b) {
    while (b > 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

/* Main function */
int main() {
    int i, j, n;
    for (i = 1; i < MAX_N; i++)
        for (j = i + 1; j <= MAX_N; j++)
            table[i - 1][j - 2] = gcd(i, j);
    for (n = 2; n <= MAX_N; n++)
        for (i = 1, sum[n - 2] = 0; i < n; i++)
            for (j = i + 1; j <= n; j++)
                sum[n - 2] += table[i - 1][j - 2];
    while (scanf("%d", &n) != EOF && n > 0)
        printf("%d\n", sum[n - 2]);
    return EXIT_SUCCESS;
}
