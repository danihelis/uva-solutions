/* 852
 * Deciding victory in Go
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  11
#define DIMENSION   9
#define NUM_DIR     4

#define EMPTY       '.'
#define BLACK       'X'
#define WHITE       'O'
#define VISITED     '+'

typedef char string_t[MAX_STRING];

string_t grid[DIMENSION];
int black, white;

/* Fill region and count points */
#define IS_IN(x) ((x) >= 0 && (x) < DIMENSION)
void fill_region(int r, int c) {
    struct { int row, col; } stack[DIMENSION * DIMENSION];
    int drow[NUM_DIR] = {-1, 0, 1, 0}, dcol[NUM_DIR] = {0, 1, 0, -1};
    int top, i, is_white, is_black, count;
    stack[0].row = r, stack[0].col = c;
    is_white = 0, is_black = 0;
    top = 1, count = 0;
    grid[r][c] = VISITED;
    while (top > 0) {
        count++, top--;
        r = stack[top].row, c = stack[top].col;
        for (i = 0; i < NUM_DIR; i++) {
            int nr = r + drow[i], nc = c + dcol[i];
            if (IS_IN(nr) && IS_IN(nc)) {
                switch (grid[nr][nc]) {
                    case WHITE: is_white = 1; break;
                    case BLACK: is_black = 1; break;
                    case EMPTY: grid[nr][nc] = VISITED;
                                stack[top].row = nr, stack[top].col = nc;
                                top++;
                }
            }
        }
    }
    if (is_white && !is_black) {
        white += count;
    }
    else if (is_black && !is_white) {
        black += count;
    }
}

/* Count blacks and whites */
void count_points() {
    int r, c;
    char *pos;
    for (r = 0, black = 0, white = 0; r < DIMENSION; r++) {
        for (c = 0, pos = grid[r]; c < DIMENSION; c++, pos++) {
            switch (*pos) {
                case BLACK: black++; break;
                case WHITE: white++; break;
                case EMPTY: fill_region(r, c); break;
            }
        }
    }
}

/* Main function */
int main() {
    int i, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        for (i = 0; i < DIMENSION; i++) {
            assert(scanf(" %s", grid[i]) != EOF);
        }
        count_points();
        printf("Black %d White %d\n", black, white);
    }
    return 0;
}
