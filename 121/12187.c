/* 12187
 * Brothers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define NUM_DIR     4
#define IN(x,max)   ((x) >= 0 && (x) < (max))
#define HATER(x)    (((x) + n - 1) % n)

/* Main function */
int main() {
    int land[MAX_DIM][MAX_DIM], next[MAX_DIM][MAX_DIM];
    int drow[NUM_DIR] = {0, 1, 0, -1}, dcol[NUM_DIR] = {1, 0, -1, 0};
    int r, c, d, n, rows, cols, battles;
    while (scanf("%d %d %d %d", &n, &rows, &cols, &battles) == 4 && n > 0) {
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                assert(scanf("%d", &land[r][c]) == 1);
            }
        }
        while (battles-- > 0) {
            for (r = 0; r < rows; r++) {
                for (c = 0; c < cols; c++) {
                    int change = 0, hater = HATER(land[r][c]);
                    for (d = 0; !change && d < NUM_DIR; d++) {
                        int nr = r + drow[d], nc = c + dcol[d];
                        change = (IN(nr, rows) && IN(nc, cols) &&
                                land[nr][nc] == hater);
                    }
                    next[r][c] = change ? hater : land[r][c];
                }
            }
            for (r = 0; r < rows; r++) {
                for (c = 0; c < cols; c++) {
                    land[r][c] = next[r][c];
                }
            }
        }
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                printf("%d%c", land[r][c], c < cols - 1 ? ' ': '\n');
            }
        }
    }
    return EXIT_SUCCESS;
}
