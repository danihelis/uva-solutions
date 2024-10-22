/* 696
 * How Many Knights
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CEIL_HALF(x)    (((x) + 1) / 2)
#define FLOOR_HALF(x)   ((x) / 2)

#define MIN(x,y)        ((x) < (y) ? (x) : (y))
#define DOUBLE_ROW(i)   (4 * (i / 4) + 2 * MIN(i % 4, 2))

/* Main function */
int main() {
    int r, c, k;
    while (scanf("%d %d", &r, &c) != EOF && (r > 0 || c > 0)) {
        if (r <= 1 || c <= 1) {
            k = r * c;
        }
        else if (r == 2 || c == 2) {
            k = r == 2 ? DOUBLE_ROW(c) : DOUBLE_ROW(r);
        }
        else {
            k = FLOOR_HALF(r) * (FLOOR_HALF(c) + CEIL_HALF(c)) + (r % 2 == 1 ? CEIL_HALF(c) : 0);
        }
        printf("%d knights may be placed on a %d row %d column board.\n", k, r, c);
    }
    return 0;
}
