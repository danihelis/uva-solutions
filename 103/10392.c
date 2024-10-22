/* 10392
 * Factoring Large Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_TESTS       20
#define MAX_FACTORS     64

long factors[MAX_FACTORS];
int num_factors;

/* Sum in modulo */
unsigned long sum_mod(unsigned long a, unsigned long b, unsigned long n) {
    return (a + b) % n;
}

/* Multiplication in modulo */
long multi_mod(long a, long b, long n) {
    long r = 0;
    a %= n;
    while (b > 0) {
        if (b & 1)
            r = sum_mod(r, a, n);
        a = sum_mod(a, a, n);
        b >>= 1;
    }
    return r;
}

/* Exponentiation in modulo */
long exp_mod(long a, long b, long n) {
    long r = 1;
    a %= n;
    while (b > 0) {
        if (b & 1)
            r = multi_mod(r, a, n);
        a = multi_mod(a, a, n);
        b >>= 1;
    }
    return r;
}

/* Random in modulo */
long rand_mod(long n) {
    unsigned long r = ((unsigned long) rand() << 32) + rand();
    return r % n;
}

/* Miller-Rabin's primality test */
int miller_rabin_test(long a, long d, long n) {
    long x = exp_mod(a, d, n); /* a^d mod n,  d = (n-1)/2^t */
    if (x == 1 || x == n - 1)
        return 1; /* possibly prime */
    while (d < n - 1) {
        x = multi_mod(x, x, n);
        d *= 2;
        if (x == 1)
            return 0; /* composite */
        if (x == n - 1)
            return 1; /* possibly prime */
    }
    return 0; /* composite */
}

/* Whether N is prime */
int is_prime(long n) {
    long a, d;
    int s;
    /* Particular cases */
    if (n % 2 == 0)
        return 0;
    else if (n <= 3)
        return 1;
    /* Compute d = (n-1)/2^t, used in the test */
    for (d = n - 1; d % 2 == 0; d /= 2)
        ;
    /* Test up to s random numbers */
    for (s = NUM_TESTS; s > 0; s--) {
        a = rand_mod(n - 3) + 2;
        if (!miller_rabin_test(a, d, n))
            return 0; /* composite */
    }
    return 1; /* probably prime */
}

/* Greatest common divisor */
long gcd(long a, long b) {
    while (b > 0) {
        long rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

/* Pollard's Rho heuristic for decomposition */
long pollard_rho(long n) {
    long x, y, c, factor;
    x = y = c = 0;
    do {
        if (x == y) {
            x = y = rand_mod(n - 2) + 2;
            c = rand_mod(n - 2) + 2;
        }
        x = sum_mod(multi_mod(x, x, n), c, n);
        y = sum_mod(multi_mod(y, y, n), c, n);
        y = sum_mod(multi_mod(y, y, n), c, n);
        factor = gcd((x < y ? y - x : x - y), n);
    } while (factor == 1 || factor == n);
    return factor;
}

/* Factor decomposition */
void decompose(long n) {
    if (n == 1)
        return;
    if (is_prime(n))
        factors[num_factors++] = n;
    else {
        long rho = pollard_rho(n);
        decompose(rho);
        decompose(n / rho);
    }
}

/* Compare longs */
int compare(const void *a, const void *b) {
    long x = * (long *) a, y = * (long *) b;
    return x < y ? -1 : x > y ? 1 : 0;
}

/* Main function */
int main() {
    long n;
    while (scanf("%ld", &n) == 1 && n > 0) {
        int i;
        for (num_factors = 0; n % 2 == 0; n /= 2)
            factors[num_factors++] = 2;
        decompose(n);
        qsort(factors, num_factors, sizeof (long), compare);
        for (i = 0; i < num_factors; i++)
            printf("    %ld\n", factors[i]);
        puts("");
    }
    return EXIT_SUCCESS;
}
