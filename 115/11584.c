/* 11584
 * Partitioning by Palindromes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX_STRING  (MAX_N + 2)

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        char string[MAX_STRING];
        char palindrome[MAX_STRING][MAX_STRING];
        int partitions[MAX_STRING];
        int i, j, k, n;
        assert(scanf(" %s", string) != EOF);
        n = strlen(string);
        for (k = 0; k < n; k++) {
            for (i = 0, j = k; j < n; i++, j++) {
                palindrome[i][j] = i == j || (string[i] == string[j] &&
                        (j == i + 1 || palindrome[i + 1][j - 1]));
            }
        }
        for (i = n - 1; i >= 0; i--) {
            if (palindrome[i][n - 1]) partitions[i] = 1;
            else {
                partitions[i] = n;
                for (j = i; j < n - 1; j++) {
                    if (palindrome[i][j]) {
                        int sum = 1 + partitions[j + 1];
                        if (sum < partitions[i]) partitions[i] = sum;
                    }
                }
            }
        }
        printf("%d\n", partitions[0]);
    }
    return EXIT_SUCCESS;
}
