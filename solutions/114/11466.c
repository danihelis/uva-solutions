/* 11466
 * Largest Prime Divisor
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

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
    if (n % 2 == 0)
        return 2;
    x = y = rand() % (n - 2) + 2;
    c = rand() % (n - 2) + 1;
    do {
        x = (prod_mod(x, x, n) + c) % n;
        y = (prod_mod(y, y, n) + c) % n;
        y = (prod_mod(y, y, n) + c) % n;
        factor = gcd(labs(x - y), n);
        if (factor == n || x == y) {
            x = y = rand() % (n - 2) + 1;
            c = rand() % (n - 2) + 1;
        }
    } while (factor == 1 || factor == n);
    return factor;
}

/* Largest prime factor */
long largest_prime_factor(long n, char any) {
    if (is_probably_prime(n))
        return any ? n : -1;
    else {
        long factor;
        factor = find_factor(n);
        do {
            n /= factor;
        } while (n % factor == 0);
        if (n == 1)
            return largest_prime_factor(factor, any);
        else {
            long a = largest_prime_factor(factor, 1);
            long b = largest_prime_factor(n, 1);
            return a > b ? a : b;
        }
    }
}

/* Main function */
int main() {
    long n;
    srand(0);
    while (scanf("%ld", &n) != EOF && n != 0)
        printf("%ld\n", largest_prime_factor(labs(n), 0));
    return EXIT_SUCCESS;
}
