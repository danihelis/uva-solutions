/* 11565
 * Simple Equations
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SWAP(v1,v2)   do { \
        int swap = v1; \
        v1 = v2; \
        v2 = swap; \
    } while (0)

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int a, b, c, x, y, z, found;
        assert(scanf("%d %d %d", &a, &b, &c) != EOF);
        for (x = 1, found = 0; !found && x <= b; x++) {
            if (b % x == 0) {
                int ap = a - x, bp = b / x;
                int d, k, delta = ap * ap - 4 * bp;
                if (delta < 0)
                    continue;
                d = sqrt(delta);
                if (d * d != delta)
                    continue;
                for (k = -1; !found && k <= 1; k += 2) {
                    y = (ap + d * k) / 2;
                    z = ap - y;
                    found = x != y && x != z && y != z && 
                        (x + y + z == a) && (x * y * z == b) &&
                        (x * x + y * y + z * z == c);
                }
            }
            if (found)
                break;
        }
        if (found) {
            if (y < x)
                SWAP(x, y);
            if (z < x)
                SWAP(x, z);
            if (z < y)
                SWAP(y, z);
            printf("%d %d %d\n", x, y, z);
        }
        else
            printf("No solution.\n");
    }
    return EXIT_SUCCESS;
}
