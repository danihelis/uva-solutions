/* 10090
 * Marbles
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CEIL(x,y)   ((x) <= 0 ? (x) / (y) : ((x) + (y) - 1) / (y))

/* Extended Euclides */
#define SWAP(v1, v2, exp) do { \
        long new_v2 = exp; v1 = v2; v2 = new_v2; \
    } while (0)
long xgcd(long a, long b, long *x, long *y) {
    long x0 = 1, x1 = 0, y0 = 0, y1 = 1;
    while (b > 0) {
        long q = a / b;
        SWAP(a, b, a % b);
        SWAP(x0, x1, x0 - x1 * q);
        SWAP(y0, y1, y0 - y1 * q);
    }
    *x = x0, *y = y0;
    return a;
}

/* Compute solution, if any */
long compute_best(long n, long c1, long n1, long c2, long n2, 
        long *x, long *y) {
    long a, b, g, k, c = -1, u1, u2;
    g = xgcd(n1, n2, &a, &b);
    if (n % g != 0)
        return 0;
    a *= n / g, b *= n / g, n1 /= g, n2 /= g;
    k = CEIL(0 - a, n2);
    u1 = a + k * n2, u2 = b - k * n1;
    if (u2 < 0)
        return 0;
    *x = u1, *y = u2;
    c = c1 * u1 + c2 * u2;
    k = CEIL(0 - b, n1);
    u1 = a - k * n2, u2 = b + k * n1;
    if (c1 * u1 + c2 * u2 < c)
        *x = u1, *y = u2;
    return 1;
}

/* Main function */
long main() {
    long n, c1, n1, c2, n2, x, y;
    while (scanf("%ld", &n) != EOF && n > 0) {
        assert(scanf("%ld %ld %ld %ld", &c1, &n1, &c2, &n2) != EOF);
        if (compute_best(n, c1, n1, c2, n2, &x, &y))
            printf("%ld %ld\n", x, y);
        else
            printf("failed\n");
    }
    return EXIT_SUCCESS;
}
