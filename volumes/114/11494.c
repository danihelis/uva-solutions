/* 11494
 * Queen
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int x1, x2, y1, y2;
    while(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != EOF && x1 > 0) {
        int moves = 2;
        if (x1 == x2 && y1 == y2)
            moves = 0;
        else if (x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2))
            moves = 1;
        printf("%d\n", moves);
    }
    return EXIT_SUCCESS;
}
