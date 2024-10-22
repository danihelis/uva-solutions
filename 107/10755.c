/* 10755
 * Garbage Heap
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     20
#define NEGATIVE    (0L - (1L << 31))

typedef long row_t[MAX_DIM];
typedef row_t page_t[MAX_DIM];
typedef page_t cube_t[MAX_DIM];

/* Compute maximum sum in a row */
long max_sum_row(row_t row, int n) {
    int i;
    long s, max;
    for (i = 0, s = 0, max = NEGATIVE; i < n; i++) {
        s = row[i] + (s > 0 ? s : 0);
        if (s > max)
            max = s;
    }
    return max;
}

/* Compute maximum sum in a page */
long max_sum_page(page_t page, int rows, int cols) {
    page_t mod;
    int i, j, k;
    long s, max;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            mod[i][j] = page[i][j];
    for (i = 0, max = NEGATIVE; i < rows; i++)
        for (k = 0; k <= i; k++) {
            if (i != k)
                for (j = 0; j < cols; j++)
                    mod[k][j] += mod[i][j];
            s = max_sum_row(mod[k], cols);
            if (s > max)
                max = s;
        }
    return max;
}

/* Compute maximum sum in a cube */
long max_sum_cube(cube_t cube, int pages, int rows, int cols) {
    int i, j, p, k;
    long s, max;
    for (p = 0, max = NEGATIVE; p < pages; p++)
        for (k = 0; k <= p; k++) {
            if (p != k)
                for (i = 0; i < rows; i++)
                    for (j = 0; j < cols; j++)
                        cube[k][i][j] += cube[p][i][j];
            s = max_sum_page(cube[k], rows, cols);
            if (s > max)
                max = s;
        }
    return max;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int pages, rows, cols, i, j, k;
        cube_t cube;
        assert(scanf("%d %d %d", &pages, &rows, &cols) != EOF);
        for (i = 0; i < pages; i++)
            for (j = 0; j < rows; j++)
                for (k = 0; k < cols; k++)
                    assert(scanf("%ld", &cube[i][j][k]) != EOF);
        printf("%ld\n%s", max_sum_cube(cube, pages, rows, cols),
                num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
