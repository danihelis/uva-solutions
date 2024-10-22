/* 11207
 * The easiest way
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, best, index;
        for (i = 0, best = -1, index = -1; i < n; i++) {
            int s1, s2, dim, small, large;
            assert(scanf("%d %d", &s1, &s2) != EOF);
            s1 *= 8, s2 *= 8;
            small = MIN(s1, s2), large = MAX(s1, s2);
            dim = MAX(small / 2, MIN(large / 4, small));
            if (dim > best)
                best = dim, index = i;
        }
        printf("%d\n", index + 1);
    }
    return EXIT_SUCCESS;
}
