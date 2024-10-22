/* 164
 * String Computer
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LETTERS     20
#define MAX_STRING      (MAX_LETTERS + 2)

typedef enum {
    SKIP,
    INSERT,
    DELETE,
    CHANGE
} edition_t;

int edition[MAX_STRING][MAX_STRING];
edition_t change[MAX_STRING][MAX_STRING];
char origin[MAX_STRING], destiny[MAX_STRING];

/* Compute lowest edition distance matrix */
void compute_edition(int *rows, int *cols) {
    int i, j;
    char *o, *d;
    edition[0][0] = 0;
    for (i = 1, d = destiny; *d != 0; i++, d++) {
        edition[0][i] = i, change[0][i] = INSERT;
    }
    for (i = 1, j = 1, o = origin; *o != 0; i++, o++) {
        edition[i][0] = i, change[i][0] = DELETE;
        for (j = 1, d = destiny; *d != 0; j++, d++) {
            if (*o == *d) {
                edition[i][j] = edition[i - 1][j - 1], change[i][j] = SKIP;
            }
            else {
                edition[i][j] = edition[i - 1][j - 1] + 1, change[i][j] = CHANGE;
                if (edition[i - 1][j] + 1 < edition[i][j]) {
                    edition[i][j] = edition[i - 1][j] + 1, change[i][j] = DELETE;
                }
                if (edition[i][j - 1] + 1 < edition[i][j]) {
                    edition[i][j] = edition[i][j - 1] + 1, change[i][j] = INSERT;
                }
            }
        }
    }
    *rows = i, *cols = j;
}

/* Recover solution and print it */
void print_solution() {
    struct { int row, col; } stack[MAX_STRING];
    int row, col, top;
    compute_edition(&row, &col);
    top = 0, row--, col--;
    while (row > 0 || col > 0) {
        if (change[row][col] == SKIP) {
            row--, col--;
        }
        else {
            stack[top].row = row, stack[top].col = col;
            row -= (change[row][col] == INSERT ? 0 : 1);
            col -= (change[stack[top].row][col] == DELETE ? 0 : 1);
            top++;
        }
    }
    for (top--; top >= 0; top--) {
        row = stack[top].row, col = stack[top].col;
        switch (change[row][col]) {
            case CHANGE: printf("C%c%02d", destiny[col - 1], col); break;
            case INSERT: printf("I%c%02d", destiny[col - 1], col); break;
            case DELETE: printf("D%c%02d", origin[row - 1], col + 1); break;
            case SKIP: assert(NULL);
        }
    }
    printf("E\n");
}

/* Main function */
int main() {
    while (scanf(" %s %s", origin, destiny) != EOF && origin[0] != '#') {
        print_solution();
    }
    return 0;
}
