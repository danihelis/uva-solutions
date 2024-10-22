/* 10673
 * Play with Floor and Ceil
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Compute GCD using Euclid's extended, such that a*x + b*y = gcd(a,b) */
#define SWAP(a,b,exp)   do { long proc = exp; a = b; b = proc; } while (0)
long xgcd(long a, long b, long *x, long *y) {
    long x0 = 1, x1 = 0, y0 = 0, y1 = 1;
    while (b > 0) {
        long q = a / b;
        SWAP(a, b, a % b);
        SWAP(x0, x1, x0 - q * x1);
        SWAP(y0, y1, y0 - q * y1);
    }
    *x = x0, *y = y0;
    return a;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        long x, k; /*, a, b, g, p, q;*/
        assert(scanf("%ld %ld", &x, &k) != EOF);
        if (x < k)
            printf("%d %ld\n", 0, x);
        else if (x % k == 0)
            printf("%ld %d\n", k, 0);
        else
            printf("%ld %ld\n", -x, x);

        /*
        a = x / k, b = (x + k - 1) / k;
        g = x / xgcd(a, b, &p, &q);
        p *= g, q *= g;
        printf("%ld %ld\n", p, q);
        fprintf(stderr, "%ld = %ld·F(%ld/%ld) + %ld·C(%ld/%ld) = "
                "%ld·%ld + %ld·%ld\n", x, p, x, k, q, x, k, p, a, q, b);
        */
    }
    return EXIT_SUCCESS;
}
