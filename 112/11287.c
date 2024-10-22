/* 11287
 * Pseudoprime Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Computes a^b mod n */
long exp_mod(long a, long b, long n) {
    long r = 1;
    a %= n;
    while (b > 0) {
        if (b & 1)
            r = (r * a) % n;
        a = (a * a) % n;
        b >>= 1;
    }
    return r;
}

/* Test used to determine if a number is prime */
int miller_rabin_test(long a, long d, long n) {
    long x = exp_mod(a, d, n); /* a^d mod n,  d = (n-1)/2^t */
    if (x == 1 || x == n - 1)
        return 1; /* possibly prime */
    while (d < n - 1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1)
            return 0; /* composite */
        if (x == n - 1)
            return 1; /* possibly prime */
    }
    return 0; /* composite */
}

/* Whether n is prime, with certainty 1 - 2^-s */
int is_prime(long n, int s) {
    long a, d;
    /* Particular cases */
    if (n % 2 == 0)
        return 0;
    else if (n <= 3)
        return 1;
    /* Compute d = (n-1)/2^t, used in the test */
    for (d = n - 1; d % 2 == 0; d /= 2)
        ;
    /* Test up to s random numbers */
    for (; s > 0; s--) {
        a = rand() % (n - 3) + 2;
        if (!miller_rabin_test(a, d, n))
            return 0; /* composite */
    }
    return 1; /* probably prime */
}

/* Main function */
int main() {
    long a, p;
    while (scanf("%ld %ld", &p, &a) != EOF && p > 0) {
        printf("%s\n",  exp_mod(a, p, p) != a || is_prime(p, 10) ? 
                "no" : "yes");
    }
    return EXIT_SUCCESS;
}
