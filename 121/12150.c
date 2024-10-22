/* 12150
 * Pole Position
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N 1000

/* Main function */
int main() {
    int n, grid[MAX_N];
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, car, delta, index, valid;
        memset(grid, 0, n * sizeof (int));
        for (i = 0, valid = 1; i < n; i++) {
            assert(scanf("%d %d", &car, &delta) != EOF);
            if (!valid) continue;
            index = i + delta;
            if (index < 0 || index >= n || grid[index]) valid = 0;
            else grid[index] = car;
        }
        if (!valid) printf("-1\n");
        else {
            for (i = 0; i < n; i++) {
                printf("%d%c", grid[i], i < n - 1 ? ' ' : '\n');
            }
        }
    }
    return EXIT_SUCCESS;
}
