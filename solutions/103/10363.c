/* 10363
 * Tic Tac Toe
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE 5
#define GRID_DIM 3

#define HAS(row, col, x) (grid[row][col] == (x) ? 1 : 0)

#define LINE(row, x) (HAS(row, 0, x) + HAS(row, 1, x) + HAS(row, 2, x) == 3)
#define COLUMN(col, x) (HAS(0, col, x) + HAS(1, col, x) + HAS(2, col, x) == 3)
#define DIAGONAL(diag, x) (HAS(0, (diag ? 0 : 2), x) + HAS(1, 1, x) + HAS(2, (diag ? 2 : 0), x) \
            == 3)

/* Main function */
int main() {
    char grid[GRID_DIM][MAX_LINE];
    int i, num_tests, exes, ohs;
    char tic_tac_toe;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        exes = 0;
        ohs = 0;
        tic_tac_toe = 0;
        for (i = 0; i < GRID_DIM; i++) {
            assert(scanf(" %s", grid[i]) != EOF);
            assert(strlen(grid[i]) == 3);
            exes += HAS(i, 0, 'X') + HAS(i, 1, 'X') + HAS(i, 2, 'X');
            ohs += HAS(i, 0, 'O') + HAS(i, 1, 'O') + HAS(i, 2, 'O');
        }
        for (i = 0; i < GRID_DIM; i++) {
            if (LINE(i, 'X') || COLUMN(i, 'X') || (i < 2 && DIAGONAL(i, 'X'))) {
                tic_tac_toe = (!tic_tac_toe || tic_tac_toe == 'X' ? 'X' : 'W');                
            }
            if (LINE(i, 'O') || COLUMN(i, 'O') || (i < 2 && DIAGONAL(i, 'O'))) {
                tic_tac_toe = (! tic_tac_toe || tic_tac_toe == 'O' ? 'O' : 'W');
            }
        }
        printf("%s\n", ((exes == ohs + 1 && (tic_tac_toe == 0 || tic_tac_toe == 'X')) || 
                    (exes == ohs && (tic_tac_toe == 0 || tic_tac_toe == 'O')) ? "yes" : "no"));
    }
    return 0;
}
