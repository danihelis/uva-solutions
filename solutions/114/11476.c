/* 11476
 * Factorizing Larget Integers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ABS(x)      ((x) >= 0 ? (x) : -(x))
    
long factors[100];
int num_factors = 0;

/* Multiplication in modulo */
long prod_mod(long a, long b, long n) {
    long r = 0;
    a %= n;
    while (b > 0) {
        if (b & 1)
            r = (r + a) % n;
        a = (a * 2) % n;
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
            r = prod_mod(r, a, n);
        a = prod_mod(a, a, n);
        b >>= 1;
    }
    return r;
}

/* Miller-Rabin test */
char witness(long a, long d, long n) {
    long x = exp_mod(a, d, n);
    if (x == 1 || x == n - 1)
        return 1;
    while (d != n - 1) {
        x = prod_mod(x, x, n);
        d *= 2;
        if (x == 1) 
            return 0;
        if (x == n - 1)
            return 1;
    }
    return 0;
}


/* Whether a number is (probably) prime */
#define MAX_ITER        10
char is_probably_prime(long n) {
    int i;
    long d;
    if (n == 4)
        return 0;
    else if (n < 4)
        return 1;
    for (d = n - 1; d % 2 == 0; d /= 2)
        ;
    for (i = MAX_ITER; i > 0; i--) {
        long a = rand() % (n - 4) + 2;
        if (!witness(a, d, n))
            return 0;
    }
    return 1;
}

/* Greatest common divisor */
long gcd(long a, long b) {
    while (b != 0) {
        long rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

/* Pollard-rho */
long find_factor(long n) {
    long x, y, c, factor;
    x = y = rand() % (n - 2) + 2;
    c = rand() % (n - 2) + 1;
    do {
        x = (prod_mod(x, x, n) + c) % n;
        y = (prod_mod(y, y, n) + c) % n;
        y = (prod_mod(y, y, n) + c) % n;
        factor = gcd(ABS(x - y), n);
        if (factor == n || x == y) {
            x = y = rand() % (n - 2) + 1;
            c = rand() % (n - 2) + 1;
        }
    } while (factor == 1 || factor == n);
    return factor;
}

/* Compare long */
int compare_long(const void *a, const void *b) {
    long x = * (long *) a, y = * (long *) b;
    return x < y ? -1 : x > y ? 1 : 0;
}

/* Factorization */
void factorization(long n) {
    for (; n % 2 == 0; n /= 2, num_factors++)
        factors[num_factors] = 2;
    if (n == 1)
        return;
    if (is_probably_prime(n))
        factors[num_factors++] = n;
    else {
        long f = find_factor(n);
        factorization(f);
        factorization(n / f);
    }
}

/* Print factors */
void print_factors(long n) {
    int i, pot;
    printf("%ld =", n);
    qsort(factors, num_factors, sizeof (long), compare_long);
    for (i = 0; i < num_factors; i++) {
        printf("%s %ld", i == 0 ? "" : " *", factors[i]);
        for (pot = 1; i < num_factors - 1 && factors[i + 1] == factors[i];
                i++, pot++)
            ;
        (pot > 1 ? printf("^%d", pot) : 0);
    }
    printf("\n");
}

/* Main function */
int main() {
    int num_tests;
    srand(0);
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        long n;
        assert(scanf("%ld", &n) != EOF);
        num_factors = 0;
        factorization(n);
        print_factors(n);
    }
    return EXIT_SUCCESS;
}
