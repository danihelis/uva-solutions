/* 260
 * Il Gioco dell'X
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     200
#define MAX_ELEMS   (MAX_DIM * MAX_DIM)
#define MAX_STRING  (MAX_DIM + 2)
#define NUM_DIR     6

#define IS_IN(v,m)  ((v) >= 0 && (v) < (m))

typedef struct {
    int row, column;
} point_t, *point_p;

char board[MAX_DIM][MAX_STRING];
int dim;
int drow[] = {-1, -1, 0, 1, 1, 0}, dcol[] = {-1, 0, 1, 1, 0, -1};

/* Check whether black wins */
int black_wins() {
    static point_t stack[MAX_ELEMS];
    int i, top = 0;
    for (i = 0; i < dim; i++) {
        if (board[0][i] == 'b') {
            stack[top].row = 0, stack[top].column = i;
            board[0][i] = 'x';
            top++;
        }
    }
    while (top > 0) {
        point_t cur = stack[--top];
        board[cur.row][cur.column] = '.';
        if (cur.row == dim - 1) {
            return 1;
        }
        for (i = 0; i < NUM_DIR; i++) {
            point_t new;
            new.row = cur.row + drow[i], new.column = cur.column + dcol[i];
            if (IS_IN(new.row, dim) && IS_IN(new.column, dim) && 
                    board[new.row][new.column] == 'b') {
                stack[top++] = new;
                board[new.row][new.column] = 'x';
            }
        }
    }
    return 0;
}

/* Main function */
int main() {
    int entry = 0;
    while (scanf("%d", &dim) != EOF && dim > 0) {
        int i;
        for (i = 0; i < dim; i++) {
            assert(scanf(" %s", board[i]) != EOF);
        }
        i = black_wins();
        printf("%d %c\n", ++entry, (i ? 'B' : 'W'));
    }
    return 0;
}
