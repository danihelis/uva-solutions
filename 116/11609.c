/* 11609
 * Teams
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MODULO  1000000007

/* Computes 2^n modulo k */
long power(long n) {
    long r = 1, p = 2;
    while (n > 0) {
        if (n & 1)
            r = (r * p) % MODULO;
        p = (p * p) % MODULO;
        n >>= 1;
    }
    return r;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        long n, r;
        assert(scanf("%ld", &n) != EOF);
        r = ((n % MODULO) * power(n - 1)) % MODULO;
        printf("Case #%d: %ld\n", test, r);
    }
    return EXIT_SUCCESS;
}
