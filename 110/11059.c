/* 11059
 * Maximum Product
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
    long test, n, i, neg, pos, max;
    for (test = 1; scanf("%ld", &n) != EOF; test++) {
        for (neg = pos = max = 0; n > 0; n--) {
            assert(scanf("%ld", &i) != EOF);
            if (i == 0)
                neg = pos = 0;
            else if (i > 0)
                neg *= i, pos = (pos > 0 ? pos * i : i);
            else {
                long lneg = neg, lpos = pos;
                pos = lneg * i, neg = (lpos > 0 ? lpos * i : i);
            }
            /*printf("[%ld] -> P=%ld  N=%ld\n", i, pos, neg);*/
            if (pos > max)
                max = pos;
        }
        printf("Case #%ld: The maximum product is %ld.\n\n", test, max);
    }
    return EXIT_SUCCESS;
}
