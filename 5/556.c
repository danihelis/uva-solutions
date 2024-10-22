/* 556
 * Amazing
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ROWS    100
#define MAX_COLS    100
#define MAX_STRING  (MAX_COLS + 2)
#define MAX_VISITED 4

typedef struct {
        int row, column;
} coord_t;

coord_t dir[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int num_dirs = sizeof (dir) / sizeof (coord_t);

signed char maze[MAX_ROWS + 2][MAX_COLS + 2];
int num_rows, num_cols;

#define MAZE(p)     (maze[(p).row][(p).column])
#define WALL(p, d)  (maze[(p).row + dir[d].row][(p).column + dir[d].column] < 0)
#define MOVE(p, d)  (p).row += dir[d].row; (p).column += dir[d].column

/* Traverse the maze, counting the number of cells visited */
void traverse() {
    coord_t start, pos;
    int r, i = 0;
    start.row = num_rows, start.column = 1;
    pos = start;
    while (start.row != pos.row || start.column != pos.column || MAZE(pos) == 0) {
#if 0
        fprintf(stderr, "POS: r=%d c=%d [%d]  DIR: r=%d c=%d | START: r=%d c=%d\n", 
                pos.row, pos.column,
                MAZE(pos), dir[i].row, dir[i].column,
                start.row, start.column);
#endif
        MAZE(pos)++;
        r = (num_dirs + i - 1) % num_dirs;
        if (!WALL(pos, r)) {
            MOVE(pos, r);
            i = r;
        }
        else {
            while (WALL(pos, i)) {
                i = (i + 1) % num_dirs;
            }
            MOVE(pos, i);
        }
    }
}

/* Main function */
int main() {
    while (scanf("%d %d ", &num_rows, &num_cols) != EOF && num_rows > 0) {
        char input[MAX_STRING];
        int i, visited[MAX_VISITED + 1];
        coord_t p;
        for (p.row = 0; p.row < num_rows + 2; p.row++) {
            if (p.row == 0 || p.row > num_rows) {
                for (p.column = 0; p.column < num_cols + 2; p.column++) {
                    MAZE(p) = -1;
                }
            }
            else {
                assert(scanf("%s ", input) != EOF);
                for (p.column = 0; p.column < num_cols + 2; p.column++) {
                    MAZE(p) = (p.column == 0 || p.column > num_cols ||
                            input[p.column - 1] != '0') ? -1 : 0;
                }
            }
        }
        traverse();
        for (i = 0; i <= MAX_VISITED; i++) {
            visited[i] = 0;
        }
        for (p.row = 1; p.row <= num_rows; p.row++) {
            for (p.column = 1; p.column <= num_cols; p.column++) {
                if (MAZE(p) >= 0) {
                    assert(MAZE(p) <= MAX_VISITED);
                    visited[MAZE(p)]++;
                }
            }
        }
        for (i = 0; i <= MAX_VISITED; i++) {
            printf("%3d", visited[i]);
        }
        printf("\n");    
    }
    return 0;
}
