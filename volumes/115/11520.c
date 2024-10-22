/* 11520
 * Fill the Square
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     10
#define MAX_STRING  (MAX_DIM + 2)
#define NUM_DIRS    4
#define IN(r,c)     ((r) >= 0 && (r) < n && (c) >= 0 && (c) < n)

char square[MAX_DIM][MAX_STRING];
int n;

/* Fill square */
void fill_square() {
    static int dr[NUM_DIRS] = {-1, 0, 1, 0}, 
               dc[NUM_DIRS] = {0, 1, 0, -1};
    int r, c, d, fit;
    char letter;
    for (r = 0; r < n; r++)
        for (c = 0; c < n; c++)
            if (square[r][c] == '.') {
                for (letter = 'A', fit = 0; !fit; letter++)
                    for (fit = 1, d = 0; fit && d < NUM_DIRS; d++) {
                        int nr = r + dr[d], nc = c + dc[d];
                        fit = !IN(nr, nc) || square[nr][nc] != letter;
                    }
                square[r][c] = --letter;

            }
}

/* Main function */
int main() {
    int i, num_tests, test;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        assert(scanf("%d", &n) == 1);
        for (i = 0; i < n; i++)
            assert(scanf(" %s", square[i]) == 1);
        fill_square();
        printf("Case %d:\n", test);
        for (i = 0; i < n; i++)
            puts(square[i]);
    }
    return EXIT_SUCCESS;
}
