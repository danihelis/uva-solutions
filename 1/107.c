/* 107
 * The Cat in the Hat
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Compute exponent */
long exponent(int n, int e) {
    long r;
    for (r = 1; e > 0; e--, r *= n)
        ;
    return r;
}

/* Main function */
int main() {
    long height, workers;
    while (scanf("%ld %ld", &height, &workers) != EOF && height > 0) {
        int level, n, found;
        for (level = 0, found = 0; level < 100; level++) {
            n = level == 0 ? 1 : pow(workers, 1.0 / (double) level) + 0.5;
            if (exponent(n + 1, level) == height) {
                found = 1;
                break;
            }
        }
        assert(found);
        printf("%ld %ld\n", n > 1 ? (workers - 1) / (n - 1) : level, 
                height * (n + 1) - workers * n);
    }
    return EXIT_SUCCESS;
}
