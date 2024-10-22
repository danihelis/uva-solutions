/* 10855
 * Rotated square
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     1000
#define MAX_STRING  (MAX_DIM + 2)

typedef char map_t[MAX_DIM][MAX_STRING];

map_t square, patch, rotation;
int dim_square, dim_patch;

/* Find patch in square */
int find_square() {
    int i, j, p, q, found, equal;
    for (i = 0, found = 0; i <= dim_square - dim_patch; i++) {
        for (j = 0; j <= dim_square - dim_patch; j++) {
            for (p = 0, equal = 1; equal && p < dim_patch; p++) {
                for (q = 0; equal && q < dim_patch; q++) {
                    equal = square[i + p][j + q] == patch[p][q];
                }
            }
            found += (equal ? 1 : 0);
        }
    }
    return found;
}

/* Rotate square */
void rotate_square() {
    int i, j;
    for (i = 0; i < dim_patch; i++) {
        for (j = 0; j < dim_patch; j++) {
            rotation[j][dim_patch - i - 1] = patch[i][j];
        }
    }
    for (i = 0; i < dim_patch; i++) {
        for (j = 0; j < dim_patch; j++) {
            patch[i][j] = rotation[i][j];
        }
    }
}

/* Main function */
int main() {
    while (scanf("%d %d", &dim_square, &dim_patch) != EOF && 
            (dim_square > 0 || dim_patch > 0)) {
        int i;
        for (i = 0; i < dim_square; i++) {
            assert(scanf(" %s", square[i]) != EOF);
        }
        for (i = 0; i < dim_patch; i++) {
            assert(scanf(" %s", patch[i]) != EOF);
        }
        for (i = 0; i < 4; i++) {
            if (i != 0) {
                rotate_square();
                printf(" ");
            }
            printf("%d", find_square());
        }
        printf("\n");
    }
    return 0;
}
