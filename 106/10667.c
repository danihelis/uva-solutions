/* 10667
 * Largest Block
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION 100

char matrix[MAX_DIMENSION][MAX_DIMENSION];
int dimension;

/* Fill a submatrix with zeroes */
void fill_block(int r1, int c1, int r2, int c2) {
    int i, j;
    for (i = r1 - 1; i < r2; i++) {
        for (j = c1 - 1; j < c2; j++) {
            matrix[i][j] = 0;
        }
    }
}

/* Get the largest submatrix of ones */
int get_largest_area() {
    int i, j, largest;
    for (i = 0, largest = 0; i < dimension; i++) {
        for (j = i; j >= 0; j--) {
            int k, maximum, sequence;
            for (k = 0, maximum = 0, sequence = 0; k < dimension; k++) {
                matrix[j][k] *= matrix[i][k];
                sequence = (matrix[j][k] ? sequence + 1 : 0);
                if (sequence > maximum) {
                    maximum = sequence;
                }
            }
            maximum *= i - j + 1;
            if (maximum > largest) {
                largest = maximum;
            }
        }
    }
    return largest;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int num_blocks, r1, r2, c1, c2;
        assert(scanf("%d %d", &dimension, &num_blocks) != EOF);
        memset(matrix, 1, MAX_DIMENSION * MAX_DIMENSION);
        for (; num_blocks > 0; num_blocks--) {
            assert(scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != EOF);
            fill_block(r1, c1, r2, c2);
        }
        printf("%d\n", get_largest_area());
    }
    return 0;
}
