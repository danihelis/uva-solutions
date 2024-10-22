/* 116
 * Unidirectional TSP
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 100

typedef struct {
    int cost, minimal, next;
} cell_t, *cell_p;

cell_t matrix[MAX_ROWS][MAX_COLUMNS];
int rows, columns;

/* Compute matrix of minimal distance, and return the row with lowest cost */
int compute_minimal_matrix() {
    int i, j, k, minimum;
    for (j = columns - 1; j >= 0; j--) {
        for (i = 0; i < rows; i++) {
            cell_p cell = &matrix[i][j];
            cell->minimal = 0;
            if (j < columns - 1) {
                for (k = 0; k < 3; k++) {
                    int next = (i + rows - 1 + k) % rows;
                    cell_p next_cell = &matrix[next][j + 1];
                    if (k == 0 || next_cell->minimal < cell->minimal || (next_cell->minimal ==
                            cell->minimal && next < cell->next)) {
                        cell->minimal = next_cell->minimal;
                        cell->next = next;
                    }
                }
            }
            cell->minimal += cell->cost;
        }
    }
    for (i = 1, minimum = 0; i < rows; i++) {
        if (matrix[i][0].minimal < matrix[minimum][0].minimal) {
            minimum = i;
        }
    }
    return minimum;
}

/* Main function */
int main() {
    while (scanf("%d %d", &rows, &columns) != EOF) {
        int i, j, minimum;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                assert(scanf("%d", &matrix[i][j].cost) != EOF);
            }
        }
        minimum = compute_minimal_matrix();
        for (i = minimum, j = 0; j < columns; j++) {
            printf("%d%c", i + 1, (j == columns -1 ? '\n' : ' '));
            i = matrix[i][j].next;
        }
        printf("%d\n", matrix[minimum][0].minimal);
    }
    return 0;
}
