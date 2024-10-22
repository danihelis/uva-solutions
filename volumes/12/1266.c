/* 1266
 * Magic Square
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   15

int matrix[MAX_N][MAX_N];

/* Fill in matrix */
void fill_matrix(int n, int max) {
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matrix[i][j] = 0;
    for (k = 1, i = 0, j = n / 2; k <= max; k++) {
        int ni, nj;
        matrix[i][j] = k;
        ni = (i + n - 1) % n;
        nj = (j + 1) % n;
        if (matrix[ni][nj] != 0)
            i = (i + 1) % n;
        else
            i = ni, j = nj;
    }
}

/* Main function */
int main() {
    int n, first = 1;
    while (scanf("%d", &n) != EOF) {
        int i, j, max, sum, digits;
        char spec[10];
        max = n * n, digits = 0;
        sum = n * (max / 2 + 1);
        fill_matrix(n, max);
        while (max > 0)
            digits++, max /= 10;
        (first ? (first = 0) : printf("\n"));
        printf("n=%d, sum=%d\n", n, sum);
        sprintf(spec, "%%%dd", digits + 1);
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                printf(spec, matrix[i][j]);
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
