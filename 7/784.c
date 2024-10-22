/* 784
 * Maze Exploration
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100
#define MAX_HEIGHT  40
#define NUM_DIR     4

#define START       '*'
#define SPACE       ' '
#define END         '_'
#define VISITED     '#'

typedef char string_t[MAX_STRING];

string_t maze[MAX_HEIGHT];
int height;

/* Fill maze from start position */
void fill_maze(int r, int c) {
    struct { int row, col; } stack[MAX_STRING * MAX_HEIGHT];
    int drow[NUM_DIR] = {-1, 0, 1, 0}, dcol[NUM_DIR] = {0, 1, 0, -1};
    int top, i;
    stack[0].row = r, stack[0].col = c;
    maze[r][c] = VISITED;
    top = 1;
    while (top > 0) {
        top--;
        r = stack[top].row, c = stack[top].col;
        for (i = 0; i < NUM_DIR; i++) {
            int nr = r + drow[i], nc = c + dcol[i];
            if (nr >= 0 && nr < height && nc >= 0 && maze[nr][nc] == SPACE) {
                maze[nr][nc] = VISITED;
                stack[top].row = nr, stack[top].col = nc;
                top++;
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests, row, col;
    assert(fgets(maze[0], MAX_STRING, stdin) != NULL);
    assert(sscanf(maze[0], "%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        height = 0, row = -1, col = -1;
        while (fgets(maze[height], MAX_STRING, stdin) != NULL && maze[height][0] != END) {
            char *start = strchr(maze[height], START);
            if (start != NULL) {
                row = height, col = start - maze[height];
            }
            height++;
        }
        assert(row != -1 && col != -1);
        fill_maze(row, col);
        for (row = 0; row <= height; row++) {
            printf("%s", maze[row]);
        }
    }

    return 0;
}
