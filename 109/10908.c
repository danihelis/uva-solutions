/* 10908
 * Largest Square
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION   100
#define MAX_STRING      (MAX_DIMENSION + 2)
#define NUM_NEIGHBOURS  8

typedef struct {
    int row, col;
} cell_t, *cell_p;

char matrix[MAX_DIMENSION][MAX_STRING];
int size[MAX_DIMENSION][MAX_DIMENSION];
int rows, columns;

int drow[NUM_NEIGHBOURS] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dcol[NUM_NEIGHBOURS] = {-1, 0, 1, 1, 1, 0, -1, -1};

/* Determine the size of each centred square in the matrix */
void determine_sizes() {
    cell_t unprocessed[MAX_DIMENSION * MAX_DIMENSION], future[MAX_DIMENSION * MAX_DIMENSION];
    int i, j, d, current_size, num_unprocessed = 0, num_future = 0;
    memset(size, 0, rows * MAX_DIMENSION * sizeof (int));
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            char is_equal = 1;
            for (d = 0; d < NUM_NEIGHBOURS && is_equal; d++) {
                int nrow = i + drow[d], ncol = j + dcol[d];
                if (nrow < 0 || nrow >= rows || ncol < 0 || ncol >= columns) {
                    is_equal = 0;
                    break;
                }
                is_equal = (matrix[i][j] == matrix[nrow][ncol]);
            }
            if (!is_equal) {
                size[i][j] = 1;
            }
            else {
                unprocessed[num_unprocessed].row = i;
                unprocessed[num_unprocessed].col = j;
                num_unprocessed++;
            }
        }
    }
    current_size = 3;
    while (num_unprocessed > 0) {
        for (i = 0, num_future = 0; i < num_unprocessed; i++) {
            cell_p cell = &unprocessed[i];
            char is_set = 0;
            for (d = 0; d < NUM_NEIGHBOURS && !is_set; d++) {
                int nvalue = size[cell->row + drow[d]][cell->col + dcol[d]];
                is_set = (nvalue > 0 && nvalue < current_size);
            }
            if (is_set) {
                size[cell->row][cell->col] = current_size;
            }
            else {
                future[num_future++] = *cell;
            }
        }
        memcpy(unprocessed, future, num_future * sizeof (cell_t));
        num_unprocessed = num_future;
        current_size += 2;
    }    
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_querries;
        assert(scanf("%d %d %d ", &rows, &columns, &num_querries) != EOF);
        printf("%d %d %d\n", rows, columns, num_querries);
        for (i = 0; i < rows; i++) {
            assert(fgets(matrix[i], MAX_STRING, stdin) != NULL);
        }
        determine_sizes();        
        for (i = 0; i < num_querries; i++) {
            cell_t cell;
            assert(scanf("%d %d", &cell.row, &cell.col) != EOF);
            printf("%d\n", size[cell.row][cell.col]);
        }
    }
    return 0;
}
