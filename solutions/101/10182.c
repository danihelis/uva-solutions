/* 10182
 * Bee Maja
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define DIM 6

/* Main function */
int main() {
    int grdx[DIM] = {1, 1, 0, -1, -1, 0},
        grdy[DIM] = {-1, 0, 1, 1, 0, -1};
    int xbase[DIM] = {0, -1, -1, 0, 1, 1},
        ybase[DIM] = {1, 1, 0, -1, -1, 0};
    int n, i, m, p, x, y;
    while (scanf("%d", &n) != EOF) {
        m = ceil((sqrt(12 * n - 3) - 3) / 6);
        p = m * m * 3 - 2 * m + 1;
        for (i = x = y = 0; i < DIM; i++, p += m)
            if (n <= p) {
                int d = p - n;
                x = xbase[i] * m + grdx[i] * d;
                y = ybase[i] * m + grdy[i] * d;
                break;
            }
        printf("%d %d\n", x, y);
    }
    return EXIT_SUCCESS;
}
