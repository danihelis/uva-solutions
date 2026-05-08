/* 11040
 * Add bricks in the wall
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM     9


/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int pyramid[DIM][DIM];
        int r, c;

        for (r = 0; r < DIM; r += 2) {
            for (c = 0; c <= r; c += 2) {
                assert(scanf("%d", &pyramid[r][c]) == 1);
            }
        }

        for (c = 1; c < DIM; c += 2) {
            pyramid[DIM - 1][c] = (pyramid[DIM - 3][c - 1] -
                    pyramid[DIM - 1][c  - 1] - pyramid[DIM - 1][c + 1]) / 2;
        }

        for (r = DIM - 2; r >= 0; r--) {
            for (c = 0; c <= r; c++) {
                pyramid[r][c] = pyramid[r + 1][c] + pyramid[r + 1][c + 1];
            }
        }

        for (r = 0; r < DIM; r++) {
            for (c = 0; c <= r; c++) {
                printf("%d%c", pyramid[r][c], c == r ? '\n' : ' ');
            }
        }
    }

    return EXIT_SUCCESS;
}
