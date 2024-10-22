/* 11138
 * Nuts and Bolts
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   500
#define EPS     1e-5
#define ZERO(x) (fabs(x) < EPS)

double matrix[MAX_N][MAX_N];
int rows, cols;

/* Compute rank of matrix */
int compute_rank() {
    int rank, r, i, c, j;
    r = c = rank = 0; 
    while (c < cols && r < rows) {
        if (ZERO(matrix[r][c])) {
            char pivot = 0;
            for (i = r + 1; !pivot && i < rows; i++)
                if (!ZERO(matrix[i][c])) {
                    for (j = c; j < cols; j++)
                        matrix[r][j] += matrix[i][j];
                    pivot = 1;
                }
            if (!pivot) {
                c++;
                continue;
            }
        }
        rank++;
        for (i = r + 1; i < rows; i++)
            if (!ZERO(matrix[i][c])) {
                double m = -1 * matrix[i][c] / matrix[r][c];
                for (j = c; j < cols; j++)
                    matrix[i][j] += matrix[r][j] * m;
                assert(ZERO(matrix[i][c]));
            }
        r++, c++;
    }
    return rank;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int r, c;
        assert(scanf("%d %d", &rows, &cols) == 2);
        for (r = 0; r < rows; r++)
            for (c = 0; c < cols; c++) {
                int v;
                assert(scanf("%d", &v) == 1);
                matrix[r][c] = v * (r * cols + c + 100);
            }

        printf("Case %d: a maximum of %d nuts and bolts "
                "can be fitted together\n", test, compute_rank());
    }
    return EXIT_SUCCESS;
}
