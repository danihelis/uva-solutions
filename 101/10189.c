/* 10189
 * Minesweeper
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_STRING  (MAX_DIM + 3)
#define NUM_DIRECT  8

#define IS_IN(x,y)  ((x) >= 0 && (x) < row && (y) >= 0 && (y) < col)

char mine[MAX_DIM][MAX_STRING];
int drow[NUM_DIRECT] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dcol[NUM_DIRECT] = {0, 1, 1, 1, 0, -1, -1, -1};

/* Main function */
int main() {
    int row, col, test = 0;
    while (scanf("%d %d", &row, &col) != EOF && row > 0 && col > 0) {
        int i, j, k;
        for (i = 0; i < row; i++) {
            char *c;
            assert(scanf(" %s", mine[i]) != EOF);
            for (c = mine[i]; *c != 0; c++) {
                if (*c == '.') {
                    *c = '0';
                }
            }
        }
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (mine[i][j] == '*') {
                    for (k = 0; k < NUM_DIRECT; k++) {
                        int r = i + drow[k], c = j + dcol[k];
                        if (IS_IN(r, c) && mine[r][c] != '*') {
                            mine[r][c]++;
                        }
                    }
                }
            }
        }
        printf("%sField #%d:\n", (test == 0 ? "" : "\n"), test + 1);
        for (i = 0; i < row; i++) {
            printf("%s\n", mine[i]);
        }
        test++;
    }
    return 0;
}
