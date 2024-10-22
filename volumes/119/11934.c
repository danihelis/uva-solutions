/* 11934
 * Magic Formula
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
    int a, b, c, d, max;
    while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &max) == 5 &&
            d > 0) {
        int i, p, count;
        for (i = 1, p = c, count = c % d == 0 ? 1 : 0; i <= max; i++) {
            p += b + 2 * i * a - a;
            count += (p % d == 0 ? 1 : 0);
        }
        printf("%d\n", count);
    }
    return EXIT_SUCCESS;
}
