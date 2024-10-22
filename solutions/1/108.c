/* 108
 * Maximum Sum
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION 100

int matrix[MAX_DIMENSION][MAX_DIMENSION];
int n;

/* Get the maximum sum of a sequence of values */
int get_maximum_sum(int * vector, int size) {
    int i, maximum, current;
    for (i = 0, maximum = 0, current = 0; i < size; i++) {
        current += vector[i];
        if (current > maximum) {
            maximum = current;
        }
        if (current < 0) {
            current = 0;
        }
    }
    return maximum;
}

/* Main function */
int main() {
    int i, j, maximum = 0;
    assert(scanf("%d", &n) != EOF);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            assert(scanf("%d", &matrix[i][j]) != EOF);
        }
    }
    for (i = 0; i < n; i++) {
        for (j = i; j >= 0; j--) {
            int sequence, k;
            if (j != i) {
                for (k = 0; k < n; k++) {
                    matrix[j][k] += matrix[i][k];
                }
            }
            sequence = get_maximum_sum(matrix[j], n);
            if (sequence > maximum) {
                maximum = sequence;
            }
        }
    }
    printf("%d\n", maximum);
    return 0;
}
