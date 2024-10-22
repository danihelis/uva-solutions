/* 11297
 * Census
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION 500

typedef enum {
    MAXIMUM,
    MINIMUM
} type_t;

typedef struct {
    int row, column;
} coordinate_t;

typedef struct grid_s {
    coordinate_t start, end;
    struct grid_s *subgrid[2][2];
    int greatest, lowest;
} grid_t, *grid_p;

int population[MAX_DIMENSION][MAX_DIMENSION];
int num_rows, num_columns;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Create segment (grid) tree */
grid_p create_grid(int row_start, int col_start, int row_end, int col_end) {
    int row_half = (row_start + row_end) / 2, col_half = (col_start + col_end) / 2;
    int i, j, choose;
    grid_p grid = (grid_p) malloc(sizeof (grid_t));
    grid->start.row = row_start, grid->start.column = col_start,
        grid->end.row = row_end, grid->end.column = col_end;
    memset(grid->subgrid, 0, 4 * sizeof (grid_p));
    if (row_start == row_end - 1) {
        if (col_start == col_end - 1) {
            grid->greatest = population[row_start][col_start];
            grid->lowest = grid->greatest;
            return grid;
        }
        grid->subgrid[0][0] = create_grid(row_start, col_start, row_end, col_half);
        grid->subgrid[0][1] = create_grid(row_start, col_half, row_end, col_end);
    }
    else {
        if (col_start == col_end - 1) {
            grid->subgrid[0][0] = create_grid(row_start, col_start, row_half, col_end);
            grid->subgrid[1][0] = create_grid(row_half, col_start, row_end, col_end);
        }
        else {
            grid->subgrid[0][0] = create_grid(row_start, col_start, row_half, col_half);
            grid->subgrid[0][1] = create_grid(row_start, col_half, row_half, col_end);
            grid->subgrid[1][0] = create_grid(row_half, col_start, row_end, col_half);
            grid->subgrid[1][1] = create_grid(row_half, col_half, row_end, col_end);
        }
    }
    for (i = 0, choose = 0; i < 2; i++) {
        for (j = 0; j < 2 && grid->subgrid[i][j] != NULL; j++) {
            if (!choose || grid->greatest < grid->subgrid[i][j]->greatest) {
                grid->greatest = grid->subgrid[i][j]->greatest;
            }
            if (!choose || grid->lowest > grid->subgrid[i][j]->lowest) {
                grid->lowest = grid->subgrid[i][j]->lowest;
                choose = 1;
            }
        }
    }
    assert(choose);
    return grid;
}

/* Query for region */
int query(grid_p grid, type_t which, int row_start, int col_start, int row_end, int col_end, int
        *value) {
    int i, j, row_half, col_half, local_best, best, choose;
    if (row_start >= row_end || col_start >= col_end ||
            row_start >= grid->end.row || row_end <= grid->start.row || 
            col_start >= grid->end.column || col_end <= grid->start.column) {
        return 0;
    }
    if (row_start == grid->start.row && row_end == grid->end.row &&
            col_start == grid->start.column && col_end == grid->end.column) {
        *value = (which == MAXIMUM ? grid->greatest : grid->lowest);
        return 1;
    }
    assert(grid->subgrid[0][0] != NULL);
    row_half = grid->subgrid[0][0]->end.row, col_half = grid->subgrid[0][0]->end.column;
    for (i = 0, choose = 0, best = -1; i < 2; i++) {
        for (j = 0; j < 2 && grid->subgrid[i][j] != NULL; j++) {
            if (query(grid->subgrid[i][j], which, 
                        (i == 0 ? row_start : MAX(row_half, row_start)), 
                        (j == 0 ? col_start : MAX(col_half, col_start)),
                        (i == 0 ? MIN(row_half, row_end) : row_end), 
                        (j == 0 ? MIN(col_half, col_end) : col_end),
                        &local_best)) {
                if (!choose || (which == MAXIMUM ? best < local_best : best > local_best)) {
                    best = local_best;
                    choose = 1;
                }
            }
        }
    }
    assert(choose);
    *value = best;
    return 1;
}

/* Update the value of a region */ 
void update(grid_p grid, int row, int column, int value) {
    assert(row >= grid->start.row && row < grid->end.row && 
            column >= grid->start.column && column < grid->end.column);
    if (grid->start.row == row && grid->end.row == row + 1 && 
            grid->start.column == column && grid->end.column == column + 1) {
        grid->greatest = value;
        grid->lowest = value;
    }
    else {
        int i, j, found;
        for (i = 0, found = 0; !found && i < 2; i++) {
            for (j = 0; j < 2 && !found && grid->subgrid[i][j] != NULL; j++) {
                grid_p sub = grid->subgrid[i][j];
                if (row >= sub->start.row && row < sub->end.row && 
                        column >= sub->start.column && column < sub->end.column) {
                    update(sub, row, column, value);
                    for (i = 0; i < 2; i++) {
                        for (j = 0; j < 2 && grid->subgrid[i][j] != NULL; j++) {
                            if (!found || grid->greatest < grid->subgrid[i][j]->greatest) {
                                grid->greatest = grid->subgrid[i][j]->greatest;
                            }
                            if (!found || grid->lowest > grid->subgrid[i][j]->lowest) {
                                grid->lowest = grid->subgrid[i][j]->lowest;
                                found = 1;
                            }
                        }
                    }
                    assert(found);
                }
            }
        }
        assert(found);
    }
}

/* Main function */
int main() {
    int i, j, q, value, num_queries;
    grid_p grid_tree;
    assert(scanf("%d", &num_rows) != EOF);
    num_columns = num_rows;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_columns; j++) {
            assert(scanf("%d", &population[i][j]) != EOF);
        }
    }
    grid_tree = create_grid(0, 0, num_rows, num_columns);
    assert(scanf("%d", &num_queries) != EOF);
    for (q = 0; q < num_queries; q++) {
        char option;
        assert(scanf(" %c", &option) != EOF);
        if (option == 'q') {
            coordinate_t start, end;
            assert(scanf("%d %d %d %d", &start.row, &start.column, &end.row, &end.column) != EOF);
            --start.row, --start.column;
            assert(query(grid_tree, MAXIMUM, MAX(start.row, 0), MAX(start.column, 0), 
                        MIN(end.row, num_rows), MIN(end.column, num_columns), &value));
            printf("%d", value);
            assert(query(grid_tree, MINIMUM, MAX(start.row, 0), MAX(start.column, 0), 
                        MIN(end.row, num_rows), MIN(end.column, num_columns), &value));
            printf(" %d\n", value);
        }
        else {
            assert(scanf("%d %d %d", &i, &j, &value) != EOF);
            update(grid_tree, --i, --j, value);
        }
    }
    return 0;
}
