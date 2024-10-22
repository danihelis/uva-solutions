/* 11254
 * Consecutive Integers
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
    long n;
    while (scanf("%ld", &n) == 1 && n > 0) {
        long best_a = n, best_b = n, k, b, n2, k2;
        for (k = 1, n2 = 2 * n; k * k + k < n2; k++) {
            b = n2 + k * k + k, k2 = 2 * k + 2;
            if (b % k2 == 0) {
                b = b / k2;
                best_b = b, best_a = b - k;
            }
        }
        printf("%ld = %ld + ... + %ld\n", n, best_a, best_b);
    }
    return EXIT_SUCCESS;
}
