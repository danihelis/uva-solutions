/* 10285
 * Longest Run on a Snowboard
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM         100
#define MAX_STRING      1000
#define NUM_NEIGHBOURS  4
#define IS_IN(r,c)      ((r) >= 0 && (r) < rows && (c) >= 0 && (c) < columns)

int matrix[MAX_DIM][MAX_DIM];
int best[MAX_DIM][MAX_DIM];
int drow[NUM_NEIGHBOURS] = {-1, 0, 1, 0}, dcol[NUM_NEIGHBOURS] = {0, 1, 0, -1};
int rows, columns;

/* Calculate best run */
int get_best_run(int row, int column) {
    if (best[row][column] > 0) {
        return best[row][column];
    }
    else {
        int k, best_run = 1;
        for (k = 0; k < NUM_NEIGHBOURS; k++) {
            int r = row + drow[k], c = column + dcol[k];
            if (IS_IN(r, c) && matrix[r][c] < matrix[row][column]) {
                int run = get_best_run(r, c) + 1;
                if (run > best_run) {
                    best_run = run;
                }
            }
        }
        best[row][column] = best_run;
        return best_run;
    }
}

/* Main function */
int main() {
    int num_tests, r, c, best_run;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char name[MAX_STRING];
        assert(scanf(" %s %d %d", name, &rows, &columns) != EOF);
        for (r = 0; r < rows; r++) {
            for (c = 0; c < columns; c++) {
                assert(scanf("%d", &matrix[r][c]) != EOF);
                best[r][c] = 0;
            }
        }
        for (r = 0, best_run = 0; r < rows; r++) {
            for (c = 0; c < columns; c++) {
                int run = get_best_run(r, c);
                if (run > best_run) {
                    best_run = run;
                }
            }
        }
        printf("%s: %d\n", name, best_run);
    }
    return 0;
}
