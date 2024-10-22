/* 11428
 * Cubes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

/* Main function */
int main() {
    struct {
        int x, y;
    } table[MAX_N];
    int x, y;
    long x3, y3, diff;
    memset(table, 0xff, sizeof (table));
    for (y = 1; y < MAX_N; y++) {
        y3 = (long) y * y * y;
        for (x = y + 1, diff = 0; diff < MAX_N; x++) {
            x3 = (long) x * x * x;
            diff = x3 - y3 - 1;
            if (diff < MAX_N && table[diff].x < 0)
                table[diff].x = x, table[diff].y = y;
        }
    }
    while (scanf("%d", &x) != EOF && x > 0) {
        if (table[--x].x >= 0)
            printf("%d %d\n", table[x].x, table[x].y);
        else
            printf("No solution\n");
    }
    return EXIT_SUCCESS;
}
