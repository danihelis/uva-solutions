/* 12461
 * Airplane
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Solution:
 *
 * Let T(k) denote the probability of k-th passenger taking n-th seat.
 * Then P = Sum{T(1) + ... + T(n-1)}.
 *
 * T(1) + T(2)                    + ... + T(n-1)
 * 1/n  + (1-1/n)·(1/n-1)·(1/n-1) + ...
 * 1/n  + (1/n)·(1/n-1)           + ...
 *    1/(n-1)                     + ...
 *                                and so on...
 *
 * Sum{T(1) + ... + T(k)}   = 1/(n-k+1)
 * Sum{T(1) + ... + T(n-1)} = 1/(n-(n-1)+1) = 1/2
 */

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0)
        puts("1/2");
    return EXIT_SUCCESS;
}
