/* 326
 * Extrapolation Using a Difference Table
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 10

int table[MAX_NUMBERS][MAX_NUMBERS];

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, j, k, term;
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &table[i][0]) != EOF);
            for (k = 1, j = i - 1; j >= 0; j--, k++) {
                table[j][k] = table[j + 1][k - 1] - table[j][k - 1];
            }
        }
        assert(scanf("%d", &term) != EOF);
        printf("Term %d of the sequence is ", term + n);
        for (; term > 0; term--) {
            for (j = 1, k = n - 2; j < n; j++, k--) {
                table[j][k] += table[j - 1][k + 1];
            }
        }
        printf("%d\n", table[n - 1][0]);
    }
    return 0;
}
