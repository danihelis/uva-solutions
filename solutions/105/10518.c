/* 10518
 * How Many Calls?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Compute Fib(k) % b in O(log(k)) */
void fib(long k, long b, long *fk, long *fkl) {
    if (k <= 1)
        *fk = 1, *fkl = 0;
    else {
        long fn, fnl, f2n, f2nl;
        fib(k / 2, b, &fn, &fnl);
        f2n = (((fnl + fnl + fn) % b) * fn) % b;
        f2nl = (((fn * fn) % b) + ((fnl * fnl) %b)) % b;
        if (k % 2 == 0)
            *fk = f2n, *fkl = f2nl;
        else
            *fk = (f2n + f2nl) % b, *fkl = f2n;
    }
}

/* Main function */
int main() {
    long n, b;
    int test = 0;
    while (scanf("%ld %ld", &n, &b) == 2 && b > 0) {
        long fn, fnl;
        fib(n + 1, b, &fn, &fnl);
        fnl = (((2 * fn) % b) + b - 1) % b;
        printf("Case %d: %ld %ld %ld\n", ++test, n, b, fnl);
    }
    return EXIT_SUCCESS;
}
