/* 1230
 * MODEX
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
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int x, y, n, r = 1;
        assert(scanf("%d %d %d", &x, &y, &n) != EOF);
        while (y > 0) {
            if (y & 1)
                r = (r * x) % n;
            x = (x * x) % n;
            y >>= 1;
        }
        printf("%d\n", r);
    }
    return EXIT_SUCCESS;
}
