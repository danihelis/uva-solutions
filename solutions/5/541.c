/* 541
 * Error Correction
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100

/* Main function */
int main() {
    int dim, matrix[MAX_DIM][MAX_DIM];
    while (scanf("%d", &dim) != EOF && dim > 0) {
        int i, j, sum, odd_row, odd_col, corrupt;
        for (i = 0, odd_row = -1, corrupt = 0; i < dim; i++) {
            for (j = 0, sum = 0; j < dim; j++) {
                assert(scanf("%d", &matrix[i][j]) != EOF);
                sum += matrix[i][j];
            }
            if (sum % 2 != 0) {
                corrupt = (odd_row != -1);
                odd_row = i;
            }
        }
        for (i = 0, odd_col = -1; !corrupt && i < dim; i++) {
            for (j = 0, sum = 0; j < dim; j++) {
                sum += matrix[j][i];
            }
            if (sum % 2 != 0) {
                corrupt = corrupt || (odd_col != -1);
                odd_col = i;
            }
        }
        corrupt = corrupt || (odd_row * odd_col < 0);
        if (corrupt || odd_row == -1) {
            printf("%s\n", (corrupt ? "Corrupt" : "OK"));
        }
        else {
            printf("Change bit (%d,%d)\n", odd_row + 1, odd_col + 1);
        }
    }
    return 0;
}
