/* 10309
 * Turn the Lights Off
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     10
#define MAX_STRING  (MAX_DIM + 5)
#define MAX_NAME    10000
#define NUM_NEIGH   5
#define LIGHT_OFF   '#'
#define LIGHT_ON    'O'
#define MAXIMUM     100
#define INFINITE    (MAXIMUM * 2)

typedef char matrix_t[MAX_DIM][MAX_STRING];

matrix_t original, board;

/* Switch the ligths of a lamp and its neighbours */
void switch_light(matrix_t *mat, int row, int column) {
    static int drow[NUM_NEIGH] = {0, -1, 0, 1, 0}, dcol[NUM_NEIGH] = {0, 0, 1, 0, -1};
    int k, r, c;
    for (k = 0; k < NUM_NEIGH; k++) {
        r = row + drow[k], c = column + dcol[k];
        if (r >= 0 && r < MAX_DIM && c >= 0 && c < MAX_DIM) {
            (*mat)[r][c] = ((*mat)[r][c] == LIGHT_OFF ? LIGHT_ON : LIGHT_OFF);
        }
    }
}

/* Count the number of switches to switch off all the board lights */
int switch_off_all(int switches) {
    int row, column;
    memcpy(board, original, MAX_DIM * MAX_STRING);
    for (row = 1; row < MAX_DIM; row++) {
        for (column = 0; column < MAX_DIM; column++) {
            if (board[row - 1][column] != LIGHT_OFF) {
                switches++;
                switch_light(&board, row, column);
            }
            if (row == (MAX_DIM - 1) && column > 0 && board[row][column - 1] == LIGHT_ON) {
                return INFINITE;
            }
        }
    }
    return (board[MAX_DIM - 1][MAX_DIM - 1] == LIGHT_ON ? INFINITE : switches);
}

/* Attempt to switch of the board switch only the first row */
int attempt_switch_off(int column, int switches) {
    if (column >= MAX_DIM) {
        return switch_off_all(switches);
    }
    else {
        int best = attempt_switch_off(column + 1, switches), attempt;
        switch_light(&original, 0, column);
        attempt = attempt_switch_off(column + 1, switches + 1);
        switch_light(&original, 0, column);
        return (attempt < best ? attempt : best);
    }
}

/* Main function */
int main() {
    char name[MAX_NAME];
    while (fgets(name, MAX_NAME, stdin) != NULL && strcmp(name, "end\n") != 0) {
        char *end = strchr(name, '\n');
        int row, best;
        for (row = 0; row < MAX_DIM; row++) {
            if (fgets(original[row], MAX_STRING, stdin) == NULL) {
                return 0; /* the input ended but the comparison didn't get it */
            }
        }
        *end = 0;
        best = attempt_switch_off(0, 0);
        printf("%s %d\n", name, (best <= MAXIMUM ? best : -1));
    }
    return 0;
}
