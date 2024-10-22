/* 10827
 * Maximum sum on a torus
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM 75
#define MAX_DOUBLE_DIM (2 * MAX_DIM)

int matrix[MAX_DOUBLE_DIM][MAX_DIM];
int dim;

int get_maximum(int *vector) {
    int i, minimum = 0, maximum = 0, min_cur = 0, max_cur = 0, sum = 0;
    for (i = 0; i < dim; i++) {
        min_cur += vector[i], max_cur += vector[i], sum += vector[i];
        if (min_cur < minimum) {
            minimum = min_cur;
        }
        if (max_cur > maximum) {
            maximum = max_cur;
        }
        if (min_cur > 0) {
            min_cur = 0;
        }
        if (max_cur < 0) {
            max_cur = 0;
        }
    }
    max_cur = maximum;
    if (sum - minimum > maximum) {
        maximum = sum - minimum;
    }
    return maximum;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j, length, maximum;
        assert(scanf("%d", &dim) != EOF);
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                assert(scanf("%d", &matrix[i][j]) != EOF);
                matrix[i + dim][j] = matrix[i][j];
            }
        }
        for (i = 0, maximum = 0; i < 2 * dim; i++) {
            for (j = i, length = 0; j >= 0 && length < dim; j--, length++) {
                int k, sequence;
                if (j != i) {
                    for (k = 0; k < dim; k++) {
                        matrix[j][k] += matrix[i][k];
                    }
                }
                sequence = get_maximum(matrix[j]);
                if (sequence > maximum) {
                    maximum = sequence;
                }
            }
        }
        printf("%d\n", maximum);
    }
    return 0;
}
