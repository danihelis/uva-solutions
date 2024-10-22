/* 13194
 * DPA Numbers II
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME       1000000
#define HALF_MAX_PRIME  (MAX_PRIME / 2)
#define MAX_PRIMES      100000

long prime[MAX_PRIMES];
int num_primes;

/* Compute prime numbers */
void compute_primes() {
    char composite[HALF_MAX_PRIME];
    long n, k;
    memset(composite, 0, HALF_MAX_PRIME);
    prime[0] = 2, num_primes = 1;
    for (n = 3; n < MAX_PRIME; n += 2) {
        if (!composite[n / 2]) {
            prime[num_primes++] = n;
            for (k = n * n; k < MAX_PRIME; k += 2 * n) {
                composite[k / 2] = 1;
            }
        }
    }
    assert(num_primes < MAX_PRIMES);
}

/* Calculate sum of divisors of N */
long sum_divisors(long n) {
    long divisors[MAX_PRIME], original, sum, p;
    int i, j, num_divisors, added;
    original = n;
    divisors[0] = 1, num_divisors = 1, sum = 1;
    for (i = 0; prime[i] <= n && i < num_primes; i++) {
        added = 0;
        p = prime[i];
        while (n % prime[i] == 0) {
            for (j = 0; j < num_divisors; j++) {
                long div = divisors[j] * p;
                assert(num_divisors + added < MAX_PRIME);
                divisors[num_divisors + added++] = div;
                sum += div;
            }
            p *= prime[i];
            n /= prime[i];
        }
        num_divisors += added;
    }
    if (n > 1) {
        for (j = 0; j < num_divisors; j++) {
            sum += divisors[j] * n;
        }
    }
    return sum - original;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    compute_primes();
    while (num_tests-- > 0) {
        long n, sum;
        assert(scanf("%ld", &n) == 1);
        sum = sum_divisors(n);
        printf("%s\n", n > sum ? "deficient" : n < sum ? "abundant" :
                "perfect");
    }
    return EXIT_SUCCESS;
}
