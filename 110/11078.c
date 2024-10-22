/* 11078
 * Open Credit System
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
    int n;
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) != EOF) {
        int i, value, high, max;
        for (i = 0, max = 0x80000000; i < n; i++) {
            assert(scanf("%d", &value) == 1);
            if (i == 0)
                high = value;
            else {
                if (high - value > max)
                    max = high - value;
                if (value > high)
                    high = value;
            }
        }
        printf("%d\n", max);
    }
    return EXIT_SUCCESS;
}

