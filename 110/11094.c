/* 11094
 * Continents
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     20
#define MAX_STACK   (MAX_DIM * MAX_DIM)
#define MAX_STRING  (MAX_DIM + 2)
#define MAX_DIR     4

typedef struct {
    int row, col;
} pair_t;

char map[MAX_DIM][MAX_STRING];
int rows, columns;
pair_t discard;
char land;

/* Compute area under a specific location */
int compute_area(int row, int col, int *area) {
    int drow[MAX_DIR] = {0, -1, 0, 1}, dcol[MAX_DIR] = {1, 0, -1, 0};
    int i, top, accept = 1;
    pair_t stack[MAX_STACK];

    stack[0].row = row, stack[0].col = col, top = 1;
    map[row][col]++; /* no longer land */
    *area = 0;

    while (top > 0) {
        pair_t cur = stack[--top];
        if (cur.row == discard.row && cur.col == discard.col)
            accept = 0;
        (*area)++;
        for (i = 0; i < MAX_DIR; i++) {
            pair_t new;
            new.row = cur.row + drow[i];
            new.col = (columns + cur.col + dcol[i]) % columns;
            if (new.row >= 0 && new.row < rows && 
                    map[new.row][new.col] == land) {
                map[new.row][new.col]++; /* no longer land */
                stack[top++] = new;
            }
        }
    }
    return accept;
}

/* Compute maximum area */
int compute_maximum_area() {
    int i, j, maximum, current;
    for (i = maximum = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            if (map[i][j] == land && compute_area(i, j, &current))
                if (current > maximum)
                    maximum = current;
    return maximum;
}

/* Main function */
int main() {
    while (scanf("%d %d", &rows, &columns) != EOF) {
        int i;
        for (i = 0; i < rows; i++)
            assert(scanf(" %s", map[i]) != EOF);
        assert(scanf("%d %d", &discard.row, &discard.col) != EOF);
        land = map[discard.row][discard.col];
        printf("%d\n", compute_maximum_area());
    }
    return EXIT_SUCCESS;
}
