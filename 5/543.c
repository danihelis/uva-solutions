/* 543
 * Goldbach's Conjecture
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES  100000

int prime[MAX_PRIMES];
int num_primes, last;

/* Compare integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Is a number prime? */
int is_prime(int n) {
    for (last += 2; last <= n; last += 2) {
        int i, p;
        for (i = 0, p = 1; p && i < num_primes && prime[i] * prime[i] <= last; i++) {
            p = (last % prime[i] != 0);
        }
        if (p) {
            assert(num_primes < MAX_PRIMES);
            prime[num_primes++] = last;
        }
    }
    last -= 2;
    return bsearch(&n, prime, num_primes, sizeof (int), compare) != NULL;
}

/* Find a half prime */
int find_prime_half(int n) {
    int k;
    for (k = 0; k < num_primes; k++) {
        if (is_prime(n - prime[k])) {
            return prime[k];
        }
    }
    k = sqrt(n) + 1;
    if (last <= k) {
        is_prime(k);
        return find_prime_half(n);
    }
    return -1;
}

/* Main function */
int main() {
    int n, p;
    num_primes = 0, last = 1;
    while (scanf("%d", &n) != EOF && n > 0) {
        p = find_prime_half(n);
        printf("%d = %d + %d\n", n, p, n - p);
    }
    return 0;
}
