/* 256
 * Quirksome Squares
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SQ(x)   ((x) * (x))

/* Main function */
int main() {
    int a, b, size, limit;
    while (scanf("%d", &size) != EOF) {
        char format[15];
        sprintf(format, "%%0%dd%%0%dd\n", size / 2, size / 2);
        printf(format, 0, 0);
        limit = size == 2 ? 10 : size == 4 ? 100 : size == 6 ? 1000 : 10000;
        for (a = 0; a < limit; a++) {
            int root, delta = SQ(2 * a - 1) - 4 * (SQ(a) - limit * a);
            root = delta >= 0 ? sqrt(delta) : 0;
            if (root * root == delta && root % 2 == 1) {
                b = (1 - 2 * a + root) / 2;
                printf(format, a, b);
            }
        }
    }
    return 0;
}
