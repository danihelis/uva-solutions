/* 10179
 * Irreducable Basic Fractions
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_PRIMES  100000
#define MAX_PRIME   100000

int prime[NUM_PRIMES];
int last_checked, num_primes;

/* Compare integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compute primes */
#define SQ(x) ((x) * (x))
void compute_primes(int n) {
    int k, i, is_prime;
    for (k = last_checked + 2; k <= n && k < MAX_PRIME && num_primes < NUM_PRIMES; k += 2) {
        for (i = 0, is_prime = 1; i < num_primes && SQ(prime[i]) <= k; i++) {
            if (k % prime[i] == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            prime[num_primes++] = k;
        }
    }
    last_checked = k - 2;
}


/* Is prime? */
int is_prime(int n) {
    if (n > last_checked) {
        compute_primes(n);
    }
    if (n <= last_checked) {
        int *is = (int *) bsearch(&n, prime, num_primes, sizeof (int), compare);
        return is != NULL;
    }
    else {
        int k, limit = sqrt(n);
        for (k = 0; k < num_primes && prime[k] <= limit; k++) {
            if (n % prime[k] == 0) {
                return 0;
            }
        }
        if (k < num_primes || prime[num_primes - 1] > limit) {
            return 1;
        }
        for (k = prime[num_primes - 1] + 2, limit = sqrt(n); k <= limit; k += 2) {
            if (n % k == 0) {
                return 0;
            }
        }
        return 1;
    }
}

/* Computes the totient of a number */
int totient(int n) {
    int k, p, phi;
    if (is_prime(n)) {
        return (n == 1 ? 1 : n - 1);
    }
    for (k = 0, phi = 1; k < num_primes && n > 1; k++) {
        for (p = 1; n % prime[k] == 0; n /= prime[k], p *= prime[k])
            ;
        if (p > 1) {
            phi *= p - p / prime[k];
        }
    }
    /* If n is still greater than 1, then it must be a prime number. Otherwise,
       we would have found a prime factor already, or n would be greater than its limit. */
    if (n > 1) {
        phi *= n - 1;
    }
    return phi;
}

/* Main function */
int main() {
    int n;
    prime[0] = 2, num_primes = 1, last_checked = 1;
    while (scanf("%d", &n) != EOF && n > 0) {
        printf("%d\n", totient(n));
    }
    fprintf(stderr, "NP = %d\nLP = %d\nLC = %d\n", num_primes, prime[num_primes - 1],
            last_checked);
    return 0;
}
