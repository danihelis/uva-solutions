/* 572
 * Oil Deposits
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM         100
#define MAX_STRING      (MAX_DIM + 1)
#define CHAR_OIL        '@'
#define NUM_DIR         4

#define IS_IN(x,v)      ((x) >= 0 && (x) < (v))
#define INSIDE(r,c)     (IS_IN((r), num_rows) && IS_IN((c), num_cols))

typedef struct cell_s {
    struct cell_s *set;
    char is_well, is_used;    
} cell_t, *cell_p;

cell_t grid[MAX_DIM][MAX_DIM];
int num_cols, num_rows;

/* Find set */
cell_p find_set(cell_p c) {
    if (c != c->set) {
        c->set = find_set(c->set);
    }
    return c->set;
}

/* Join sets */
void join_sets(cell_p a, cell_p b) {
    a = find_set(a), b = find_set(b);
    if (a != b) {
        a->set = b;
    }
}

/* Join all sets of oils and count them */
int join_and_count() {
    static int drow[] = {0, -1, -1, -1}, dcol[] = {-1, -1, 0, 1};
    int total, i, row, col;
    for (row = 0; row < num_rows; row++) {
        for (col = 0; col < num_cols; col++) {
            cell_p set = &grid[row][col];
            if (set->is_well) {
                for (i = 0; i < NUM_DIR; i++) {
                    int nrow = row + drow[i], ncol = col + dcol[i];
                    if (INSIDE(nrow, ncol) && grid[nrow][ncol].is_well) {
                        join_sets(set, &grid[nrow][ncol]);
                    }
                }
            }
        }
    }
    for (row = 0, total = 0; row < num_rows; row++) {
        for (col = 0; col < num_cols; col++) {
            cell_p set = &grid[row][col];
            if (set->is_well) {
                set = find_set(set);
                if (!set->is_used) {
                    total++;
                    set->is_used = 1;
                }
            }
        }
    }
    return total;
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_rows, &num_cols) != EOF && !(num_rows == 0 || num_cols == 0)) {
        int row, col;
        for (row = 0; row < num_rows; row++) {
            char string[MAX_STRING], *s;
            assert(scanf(" %s", string) != EOF);
            for (col = 0, s = string; col < num_cols; col++, s++) {
                cell_p c = &grid[row][col];
                c->is_well = (*s == CHAR_OIL);
                c->set = c, c->is_used = 0;
            }
        }
        printf("%d\n", join_and_count());
    }
    return 0;
}
