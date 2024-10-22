/* 880
 * Cantor Fractions
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
    while (scanf("%ld", &n) == 1) {
        long i, sum, num, den;
        i = (long) ceil((sqrt(1.0 + 8.0 * n) - 1.0) / 2.0);
        sum = i * (i + 1) / 2;
        num = sum - n + 1;
        den = i - num + 1;
        printf("%ld/%ld\n", num, den);
    }
    return EXIT_SUCCESS;
}
