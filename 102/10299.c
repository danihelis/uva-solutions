/* 10299
 * Relatives
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_PRIMES  50000
#define MAX_PRIME   50000

int prime[NUM_PRIMES];
int last_checked, num_primes;

/* Compute primes */
#define SQ(x) ((x) * (x))
void compute_primes(int n) {
    int i, is_p;
    for (; SQ(last_checked) <= n && last_checked < MAX_PRIME; last_checked += 2) {
        for (i = 0, is_p = 1; is_p && i < num_primes && SQ(prime[i]) <= last_checked; i++) {
            is_p = (last_checked % prime[i] != 0);
        }
        if (is_p) {
            prime[num_primes++] = last_checked;
        }
    }
}

/* Computes the totient of a number */
int totient(int n) {
    int k, p, phi;
    if (n == 1) {
        return 0;
    }
    compute_primes(n);
    for (k = 0, phi = 1; k < num_primes && prime[k] <= n; k++) {
        for (p = 1; n % prime[k] == 0; n /= prime[k], p *= prime[k])
            ;
        if (p > 1) {
            phi *= p - p / prime[k];
        }
    }
    /* If n is still greater than 1, then it must be a prime number */
    if (n > 1) {
        phi *= n - 1;
    }
    return phi; 
}

/* Main function */
int main() {
    int n;
    prime[0] = 2, num_primes = 1, last_checked = 3;
    while (scanf("%d", &n) != EOF && n > 0) {
        printf("%d\n", totient(n));
    }
    return 0;
}
