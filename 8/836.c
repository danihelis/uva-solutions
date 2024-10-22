/* 836
 * Largest Submatrix
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION 1000

char matrix[MAX_DIMENSION][MAX_DIMENSION];
int dimension;

int get_max_sequence(char *vector) {
    int i, maximum = 0, sequence = 0;
    for (i = 0; i < dimension; i++) {
        sequence = (vector[i] == '1' ? sequence + 1 : 0);
        if (sequence > maximum) {
            maximum = sequence;
        }
    }
    return maximum;
}

/* Main function */
int main() {
    int num_tests, i, j, maximum;
    assert(fgets(matrix[0], MAX_DIMENSION, stdin) != NULL);
    num_tests = atoi(matrix[0]);
    for (; num_tests > 0; num_tests--) {
        assert(fgets(matrix[0], MAX_DIMENSION, stdin) != NULL && matrix[0][0] == '\n');
        assert(fgets(matrix[0], MAX_DIMENSION, stdin) != NULL);
        dimension = strlen(matrix[0]) - 1;
        assert(dimension < MAX_DIMENSION);
        for (i = 1; i < dimension; i++) {
            assert(fgets(matrix[i], MAX_DIMENSION, stdin) != NULL);
        }
        for (i = 0, maximum = 0; i < dimension; i++) {
            for (j = i; j >= 0; j--) {
                int k, sequence;
                if (j != i) {
                    for (k = 0; k < dimension; k++) {
                        matrix[j][k] = (matrix[i][k] == '1' && matrix[j][k] == '1' ? '1' : '0');
                    }
                }
                sequence = get_max_sequence(matrix[j]) * (i - j + 1);
                if (sequence > maximum) {
                    maximum = sequence;
                }
            }
        }
        printf("%d\n%s", maximum, (num_tests > 1 ? "\n" : ""));
    }
    return 0;
}
