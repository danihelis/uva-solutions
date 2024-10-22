/* 11581
 * Grid Successors
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Get next matrix configuration */
int next(int matrix) {
    int res, i, d, sum;
    for (i = 0, res = 0; i < 9; i++) {
        for (d = i - 3, sum = 0; d <= i + 3 && d < 9; d += 2) {
            if (d >= 0 && (i != 2 || d != 3) && (i != 3 || d != 2) &&
                          (i != 5 || d != 6) && (i != 6 || d != 5)) { 
                sum += (matrix & (1 << d)) ? 1 : 0;
            }
        }
        res |= (sum % 2 == 1) ? 1 << i : 0;
    }
    return res;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char line[4];
        int i, j, matrix;
        for (i = 0, matrix = 0; i < 3; i++) {
            assert(scanf(" %s", line) != EOF);
            for (j = 0; j < 3; j++) {
                matrix |= line[j] == '1' ? 1 << (i * 3 + j) : 0;
            }
        }
        for (i = 0; matrix != 0; i++) {
            matrix = next(matrix);
        }
        printf("%d\n", i - 1);
    }
    return 0;
}
