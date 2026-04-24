/* 10177
 * (2/3/4)-D Sqr/Rects/Cubes/Boxes?
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Here is the solution for a hypercube of dimension K and size N:
 *
 * Number of squares:
 *      Sum{i = 0..N} i^K
 *
 * Number of rectangles and squares:
 *      ( Sum{i = 0..N} i )^K = ( N·(N+1)/2 )^K
 */

#define DIM(N)          (N - 2)
#define MAX_N           100

/* Main function */
int main() {
    long squares[3][MAX_N + 1];
    int n, d, i, k;

    for (d = 2; d <= 4; d++) {
        squares[DIM(d)][0] = 0;
        for (i = 1; i <= MAX_N; i++) {
            int prod = 1;
            for (k = 0; k < d; k++, prod *= i)
                ;
            squares[DIM(d)][i] = prod + squares[DIM(d)][i - 1];
        }
    }

    while (scanf("%d", &n) != EOF) {
        assert(n >= 0 && n <= MAX_N);
        for (d = 2; d <= 4; d++) {
            long term = n * (n + 1) / 2;
            long rectangles = 1;
            for (k = 0; k < d; k++, rectangles *= term)
                ;
            printf("%ld %ld%c",
                    squares[DIM(d)][n],
                    rectangles - squares[DIM(d)][n],
                    d == 4 ? '\n' : ' ');
        }
    }
    return EXIT_SUCCESS;
}
