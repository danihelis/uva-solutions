/* 10502
 * Counting Rectangles
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_STRING  (MAX_DIM + 2)

/* Main function */
int main() {
    int rows, cols;
    while (scanf("%d %d", &rows, &cols) == 2 && rows > 0) {
        char matrix[MAX_DIM][MAX_STRING];
        int i, j, r, c, win, count;
        for (i = 0; i < rows; i++)
            assert(scanf(" %s", matrix[i]) == 1);
        for (i = 0, count = 0; i < rows; i++)
            for (j = 0; j < cols; j++)
                for (r = i, win = cols; r < rows && win > j; r++) {
                    for (c = j; c < win && matrix[r][c] == '1'; c++, count++)
                        ;
                    win = c;
                }
        printf("%d\n", count);
    }
    return EXIT_SUCCESS;
}
