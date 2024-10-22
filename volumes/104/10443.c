/* 10443
 * Rock
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_STRING  (MAX_DIM + 2)
#define MATRIX_DIM  (MAX_DIM * MAX_STRING)

#define IN(v, mv)   (v >= 0 && v < mv)

int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};
char tribes[] = "SRPS";

char map[MAX_DIM][MAX_STRING];
int rows, cols;

void reshape() {
    char new_map[MAX_DIM][MAX_STRING];
    int k, r, c;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            char lose, *t = strchr(tribes, map[r][c]), *w;
            for (k = 0, lose = 0, w = t + 1; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                lose |= IN(nr, rows) && IN(nc, cols) && map[nr][nc] == *w;
            }
            new_map[r][c] = lose ? *w : *t;
        }
        new_map[r][c] = 0;
    }
    memcpy(map, new_map, rows * MAX_STRING);
}

/* Main function */
int main() {
    int r, n, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d %d %d", &rows, &cols, &n) != EOF);
        for (r = 0; r < rows; r++) {
            assert(scanf(" %s", map[r]) != EOF);
        }
        for (; n > 0; n--) {
            reshape();
        }
        for (r = 0; r < rows; r++) {
            printf("%s\n", map[r]);
        }
        (num_tests > 1 ? printf("\n") : 0);

    }
    return 0;
}
