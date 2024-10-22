/* 1180
 * Perfect Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_P   17
#define PARAM_S 10

/* Exponential mod */
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

/* Miller-Rabin's test for probabilistic primality */
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

/* Check if number if prime with 2 ^ -PARAM_S chance of error */
long is_prime(long n) {
    long a, d;
    int s;
    /* Particular cases */
    if (n % 2 == 0)
        return n == 2;
    else if (n <= 3)
        return 1;
    /* Compute d = (n-1)/2^t, used in the test */
    for (d = n - 1; d % 2 == 0; d /= 2)
        ;
    /* Test up to s random numbers */
    for (s = PARAM_S; s > 0; s--) {
        a = rand() % (n - 3) + 2;
        if (!miller_rabin_test(a, d, n))
            return 0; /* composite */
    }
    return 1; /* probably prime */
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int p, perfect = 0;
        assert(scanf("%d%*c", &p) == 1);
        if (p > 1 && p <= MAX_P && is_prime(p)) {
            perfect = is_prime((1L << p) - 1);
        }
        printf("%s\n", perfect ? "Yes" : "No");
    }
    return EXIT_SUCCESS;
}
