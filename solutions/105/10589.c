/* 10589
 * Area
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define INPUT_PR    10000000
#define OUTPUT_PR   100000

long r, r2, area, prec;

/* Whether a point is inside or not */
int inside(long x, long y) {
    long dx, dy;
    int i;
    for (i = 0; i < 4; i++) {
        dx = i % 2 == 0 ? x : r - x;
        dy = i / 2 == 0 ? y : r - y;
        if (dx * dx + dy * dy > r2)
            return 0;
    }
    return 1;
}

/* Main function */
int main() {
    int i, n, hits;
    while (scanf("%d %ld", &n, &r) != EOF && n > 0) {
        area = r * r;
        r *= INPUT_PR;
        r2 = r * r;
        for (i = 0, hits = 0; i < n; i++) {
            long xh, xl, yh, yl;
            assert(scanf("%ld.%ld %ld.%ld", &xh, &xl, &yh, &yl) != EOF);
            hits += inside(xh * INPUT_PR + xl, yh * INPUT_PR + yl);
        }
        area *= hits * OUTPUT_PR;
        for (; n > 1; area /= 10, n /= 10)
            ;
        printf("%ld.%05ld\n", area / OUTPUT_PR, area % OUTPUT_PR);
    }
    return EXIT_SUCCESS;
}
