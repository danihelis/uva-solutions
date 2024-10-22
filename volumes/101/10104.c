/* 10104
 * Euclid Problem
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Extended euclid */
#define NEXT(old,x,q) do { \
        int _old = (old); \
        (old) = (x); \
        (x) = _old - q * (x); \
    } while (0)
int gcd(int a, int b, int *s, int *t) {
    int r, old_r, old_s, old_t;
    old_r = a, r = b;
    old_s = 1, *s = 0, old_t = 0, *t = 1;
    while (r != 0) {
        int q = old_r / r;
        NEXT(old_r, r, q);
        NEXT(old_s, *s, q);
        NEXT(old_t, *t, q);
    }
    *s = old_s, *t = old_t;
    return old_r;
}

/* Main function */
int main() {
    int a, b, d, x, y;
    while (scanf("%d %d", &a, &b) != EOF) {
        d = gcd(a, b, &x, &y);
        printf("%d %d %d\n", x, y, d);
    }
    return 0;
}
