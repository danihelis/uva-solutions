/* 12488
 * Start Grid
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   24

/* Main function */
int main() {
    int grid[MAX_N], n;
    while (scanf("%d", &n) != EOF) {
        int i, j, car, overtakes;
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &grid[i]) != EOF);
        }
        for (i = overtakes = 0; i < n; i++) {
            assert(scanf("%d", &car) != EOF);
            for (j = i; j < n && grid[j] != car; j++, overtakes++)
                ;
            assert(j < n);
            for (; j > i; j--) {
                grid[j] = grid[j - 1];
            }
        }
        printf("%d\n", overtakes);
    }
    return EXIT_SUCCESS;
}
