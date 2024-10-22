/* 10268
 * 498-bis
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* P(x) = a0 + a1 · x + a2 · x^2 + ... + an · x^n
 * We can write: 
 *      P{k}(x) = ak + x · P{k+1}(x)
 *
 * Let P{n}(x) = an. Thence:
 *      P{0}(x) = a0 + x · (a1 + x · (a2 + ... + x · (an) ) ) = P(x)
 *
 * P'{k}(x) = x' · P{k+1}(x) + x · P'{k+1}(x)
 * From P{n}(x) = an, P'{n}(x) = 0, we can easily compute P'(x).
 */

/* Main function */
int main() {
    char space;
    long a, n, p, dp;
    while (scanf("%ld", &n) != EOF) {
        p = dp = 0;
        while (scanf("%ld%c", &a, &space) != EOF) {
            long np = a + n * p, ndp = n * dp + p;
            p = np, dp = ndp;
            if (space == '\n')
                break;
        }
        printf("%ld\n", dp);
    }
    return EXIT_SUCCESS;
}
