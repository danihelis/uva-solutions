/* 10718
 * Bit Mask
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
    unsigned int n, low, high, m;
    while (scanf("%u %u %u", &n, &low, &high) != EOF) {
        int i;
        for (i = 31, m = 0; i >= 0; i--) {
            if (((n & (1 << i)) != 0))
                if (m >= low || (low & (1 << i)) == 0)
                    continue;
            if ((m | (1 << i)) > high)
                continue;
            m |= 1 << i;
        }
        printf("%u\n", m);
    }
    return EXIT_SUCCESS;
}
