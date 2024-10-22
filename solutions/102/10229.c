/* 10229
 * Modular Fibonacci
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Computes F{2n} and F{2n-1} recursivelly */
void fibbo(int n, long *f2n, long *f2n1, long mod) {
    if (n <= 1)
        *f2n = *f2n1 = 1;
    else {
        long fn, fn1;
        fibbo(n / 2, &fn, &fn1, mod);
        if (n % 2 == 1) {
            long fn2 = fn1;
            fn1 = fn;
            fn = (fn1 + fn2) % mod;
        }
        *f2n = ((2 * fn1 + fn) * fn) % mod;
        *f2n1 = (fn1 * fn1 + fn * fn) % mod;
    }
}

/* Main function */
int main() {
    long n, fn, fn1, mod;
    int m;
    while (scanf("%ld %d", &n, &m) == 2) 
        if (n <= 2 || m == 0)
            printf("%d\n", m == 0 ? 0 : n == 0 ? 0 : 1);
        else {
            mod = 1 << m;
            fibbo(n / 2, &fn, &fn1, mod);
            if (n % 2 == 1)
                fn = (fn + fn1) % mod;
            printf("%ld\n", fn);
        }
    return EXIT_SUCCESS;
}
