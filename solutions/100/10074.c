/* 10074
 * Take the Land
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION 200

int matrix[MAX_DIMENSION][MAX_DIMENSION];

int get_max_sequence(int *vector, int dimension) {
    int i, maximum = 0, sequence = 0;
    for (i = 0; i < dimension; i++) {
        sequence = (vector[i] == 0 ? sequence + 1 : 0);
        if (sequence > maximum) {
            maximum = sequence;
        }
    }
    return maximum;
}

/* Main function */
int main() {
    int rows, columns, i, j, k, maximum;
    while (scanf("%d %d", &rows, &columns) != EOF && !(rows == 0 && columns == 0)) {
        for (i = 0, maximum = 0; i < rows; i++) {
            int sequence;
            for (j = 0; j < columns; j++) {
                assert(scanf("%d", &matrix[i][j]) != EOF);
            }
            sequence = get_max_sequence(matrix[i], columns);
            if (sequence > maximum) {
                maximum = sequence;
            }
            for (j = i - 1; j >= 0; j--) {
                for (k = 0; k < columns; k++) {
                    matrix[j][k] += matrix[i][k];
                }
                sequence = get_max_sequence(matrix[j], columns) * (i - j + 1);
                if (sequence > maximum) {
                    maximum = sequence;
                }
            }
        }
        printf("%d\n", maximum);
    }
    return 0;
}
