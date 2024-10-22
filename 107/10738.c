/* 10738
 * Riemann vs Mertens
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     1000010
#define MAX_PRIMES      500000

#define SQUARE(x)       ((x) * (x))

int mu[MAX_NUMBERS], merten[MAX_NUMBERS], factor[MAX_NUMBERS];
int prime[MAX_PRIMES];
int num_primes, last_number, last_prime;

/* Compute all prime numbers up to n */
void compute_prime(int n) {
    for (; last_prime <= n; last_prime += 2) {
        int k, is_p;
        for (k = 0, is_p = 1; is_p && k < num_primes && SQUARE(prime[k]) <= last_prime; k++) {
            is_p = (last_prime % prime[k] != 0);
        }
        if (is_p) {
            prime[num_primes++] = last_prime;
        }
    }
}

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compute merten function up to n */
void compute_merten(int n) {
    compute_prime(n);
    for (; last_number <= n; last_number++) {
        int k, m, *b;
        b = bsearch(&last_number, prime, num_primes, sizeof (int), compare);
        if (b != NULL) {
            k = b - prime, m = -1;
        }
        else {
            for (k = 0, m = -1; k < num_primes && prime[k] < last_number; k++) {
                if (last_number % prime[k] == 0) {
                    int v = last_number / prime[k];
                    m = (factor[v] == prime[k] ? 0 : -1 * mu[v]);
                    break;
                }
            }
        }
        factor[last_number] = prime[k];
        mu[last_number] = m;
        merten[last_number] = merten[last_number - 1] + m;
    }
}

/* Main function */
int main() {
    int n;
    prime[0] = 2, num_primes = 1, last_prime = 3;
    mu[0] = 0, merten[0] = 0, factor[0] = 1;
    mu[1] = 1, merten[1] = 1, factor[1] = 1; 
    last_number = 2;
    while (scanf("%d", &n) != EOF && n > 0) {
        compute_merten(n);
        printf("%8d%8d%8d\n", n, mu[n], merten[n]);
    }
    return 0;
}
