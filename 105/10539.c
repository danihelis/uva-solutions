/* 10539
 * Almost Prime Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 1000000

long prime[MAX_NUMBERS];
int num_primes;
long last_prime;

/* Compute primes */
#define SQ(x)   ((x) * (x))
void compute_prime(long n) {
    for (; SQ(last_prime) <= n; last_prime += 2) {
        int k, p;
        for (k = 0, p = 1; p && k < num_primes && SQ(prime[k]) <= last_prime; k++) {
            p = (last_prime % prime[k] != 0);
        }
        if (p) {
            assert(num_primes < MAX_NUMBERS);
            prime[num_primes++] = last_prime;
        }
    }
}

/* Binary search for a sqrt */
int binary_search(long n) {
    int start, end, middle;
    long d;
    start = 0, end = num_primes;
    while (start < end) {
        middle = (start + end) / 2;
        d = SQ(prime[middle]);
        if (d == n) {
            return middle;
        }
        else if (n < d) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }
    return start;
}

/* Count number of almost-primes */
int get_almost_primes(long a, long b) {
    int i, lim, total;
    long term;
    compute_prime(b);
    lim = binary_search(b);
    if (lim == num_primes) {
        lim--;
    }
    for (i = 0, total = 0; i <= lim; i++) {
        for (term = SQ(prime[i]); term <= b && term > 0; term *= prime[i]) {
            if (term >= a) {
                total++;
            }
        }
    }
    return total;
}

/* Main function */
int main() {
    int num_tests;
    prime[0] = 2, num_primes = 1, last_prime = 3;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        long s, e;
        assert(scanf("%ld %ld", &s, &e) != EOF);
        printf("%d\n", get_almost_primes(s, e));
    }
    return 0;
}
