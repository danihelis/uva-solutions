/* 10490
 * Mr. Azad and his Son!!!!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Exponential modulus */
int exp_mod(long a, int b, int n) {
    int r = 1;
    a %= n;
    while (b > 0) {
        if (b & 1)
            r = (r * a) % n;
        a = (a * a) % n;
        b >>= 1;
    }
    return r;
}

/* Miller-Rabin's test for possible primality */
int miller_rabin_test(int a, int d, int n) {
    int x = exp_mod(a, d, n); /* a^d mod n,  d = (n-1)/2^t */
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

/* Is prime with (1 - 2^-s) certainty */
int is_prime(int n, int s) {
    int a, d;
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
    int n, x;
    while (scanf("%d", &n) == 1 && n > 0) {
        x = (1 << n) - 1;
        if (is_prime(x, 10)) {
            long p = (1l << (n - 1)) * x;
            printf("Perfect: %ld!\n", p);
        }
        else if (is_prime(n, 5)) 
            printf("Given number is prime. "
                   "But, NO perfect number is available.\n");
        else
            printf("Given number is NOT prime! "
                   "NO perfect number is available.\n");
    }
    return EXIT_SUCCESS;
}
