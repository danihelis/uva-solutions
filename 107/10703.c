/* 10703
 * Free spots
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION 500
#define TOTAL_DIMENSION (MAX_DIMENSION * MAX_DIMENSION)
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

char matrix[MAX_DIMENSION][MAX_DIMENSION];

/* Main function */
int main() {
    int width, height, regions, row, col, not_covered;
    while (scanf("%d %d %d", &width, &height, &regions) != EOF) {
        if (width == 0) {
            break;
        }
        memset(matrix, 0, TOTAL_DIMENSION);
        for (; regions > 0; regions--) {
            int x1, x2, y1, y2;
            assert(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != EOF);
            x1--, x2--, y1--, y2--;
            for (row = MIN(y1, y2); row <= MAX(y1, y2); row++) {
                for (col = MIN(x1, x2); col <= MAX(x1, x2); col++) {
                    matrix[row][col] = 1;
                }
            }
        }
        not_covered = 0;
        for (row = 0; row < height; row++) {
            for (col = 0; col < width; col++) {
                not_covered += (1 - matrix[row][col]);
            }
        }
        if (not_covered <= 1) {
            printf("There is %s empty spot%s.\n", (not_covered == 0 ? "no" : "one"),
                    (not_covered == 0 ? "s" : ""));
        }
        else {
            printf("There are %d empty spots.\n", not_covered);
        }
    }
    return 0;
}
