/* 11349
 * Symmetric Matrix
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        long matrix[MAX_N][MAX_N];
        int i, j, n, sym;
        assert(scanf(" N = %d", &n) == 1);
        for (i = 0, sym = 1; i < n; i++)
            for (j = 0; j < n; j++) {
                assert(scanf("%ld", &matrix[i][j]) == 1);
                sym &= matrix[i][j] >= 0;
            }
        for (i = 0; sym && i < (n + 1) / 2; i++)
            for (j = 0; sym && j < n; j++)
                sym = matrix[i][j] == matrix[n - i - 1][n - j - 1];
        printf("Test #%d: %symmetric.\n", test, sym ? "S" : "Non-s");
    }
    return EXIT_SUCCESS;
}
