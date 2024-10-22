/* 10892
 * LCM Cardinality
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME_NUMBER    50000
#define MAX_PRIMES          (MAX_PRIME_NUMBER)
#define MAX_FACTORS         1000

#define SQUARE(x)           ((x) * (x))
#define LCM(x,y)            ((x) / gcd(x, y) * (y))

int prime[MAX_PRIMES];
int num_primes, last_number;

/* Compute all prime numbers up to n */
void compute_prime(int n) {
    for (; last_number <= n && last_number < MAX_PRIME_NUMBER; last_number += 2) {
        int k, p;
        for (k = 0, p = 1; p && k < num_primes && SQUARE(prime[k]) <= last_number; k++) {
            p = (last_number % prime[k] != 0);
        }
        if (p) {
            prime[num_primes++] = last_number;
        }
    }
}

/* Greatest common divisor */
int gcd(int a, int b) {
    int m = a % b;
    while (m != 0) {
        a = b;
        b = m;
        m = a % b;
    }
    return b;
}

/* Compute LCM caridnality */
int lcm_cardinality(int n) {
    int factor[MAX_FACTORS], total, last;
    int k, f, i, e, original_n;
    compute_prime(n);
    factor[0] = 1, total = 1, last = 1;
    for (k = 0, original_n = n; k < num_primes && prime[k] <= n && n > 1; k++) {
        for (f = prime[k], e = total; n % prime[k] == 0; f *= prime[k], n /= prime[k]) {
            for (i = 0; i < total; i++, e++) {
                assert(e < MAX_FACTORS);
                factor[e] = factor[i] * f;
            }
        }
        last = total;
        total = e;
    }
    if (n > 1) { /* The number n is prime */
        return 2;
    }
    for (i = last, k = total; i < total - 1; i++) {
        for (e = 1; e < i; e++) {
            k += (LCM(factor[i], factor[e]) == original_n ? 1 : 0);
        }
    }
    return k;
}

/* Main function */
int main() {
    int n;
    prime[0] = 2, num_primes = 1, last_number = 3;
    while (scanf("%d", &n) != EOF && n > 0) {
        printf("%d %d\n", n, lcm_cardinality(n));
    }
    return 0;
}
