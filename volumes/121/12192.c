/* 12192
 * Grapevine
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     500

int matrix[MAX_DIM][MAX_DIM], rows, cols;

/* Query matrix for a square submatrix with values in range */
int query(int low, int high) {
    int i, j, d;
    for (i = d = 0; i < rows - d && matrix[i][0] <= high; i++)
        for (j = 0; j < cols - d && matrix[i][j] <= high; j++)
            if (matrix[i][j] >= low)
                for (; i + d < rows && j + d < cols && 
                        matrix[i + d][j + d] <= high; d++)
                    ;
    return d;
}

/* Main function */
int main() {
    while (scanf("%d %d", &rows, &cols) != EOF && rows > 0) {
        int i, j, q;
        for (i = 0; i < rows; i++)
            for (j = 0; j < cols; j++)
                assert(scanf("%d", &matrix[i][j]) != EOF);
        assert(scanf("%d", &q) != EOF);
        for (; q > 0; q--) {
            assert(scanf("%d %d", &i, &j) != EOF);
            printf("%d\n", query(i, j));
        }
        printf("-\n");
    }
    return EXIT_SUCCESS;
}
