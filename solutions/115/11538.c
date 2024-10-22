/* 11538
 * Chess Queen
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    long n, m;
    while (scanf("%ld %ld", &n, &m) != EOF && n > 0) {
        long result;
        if (n < m) {
            long swap = n;
            n = m;
            m = swap;
        }
        result = m * n * (n - 1) + (9 * n - 2 * (m + 1)) * m * (m - 1) / 3;
        printf("%ld\n", result);
    }
    return EXIT_SUCCESS;
}
