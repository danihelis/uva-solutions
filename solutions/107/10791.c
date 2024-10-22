/* 10791
 * Minimum Sum LCM
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUM_PRIME   46340
#define MAX_PRIMES      10000
#define MAX_FACTORS     10

int prime[MAX_PRIMES], num_primes;
unsigned int factor[MAX_FACTORS], num_factors;

/* Compute prime numbers */
void compute_primes() {
    char composite[MAX_NUM_PRIME / 2];
    int i, k;
    memset(composite, 0, sizeof (composite));
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_NUM_PRIME / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (k = n * n; k < MAX_NUM_PRIME; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Decompose in factors */
void decompose(int number) {
    unsigned int i, n, p;
    for (i = 0, num_factors = 0, n = number; n > 1 && i < num_primes;
            i++)
        if (n % prime[i] == 0) {
            factor[num_factors] = 1, p = prime[i];
            while (n % p == 0)
                factor[num_factors] *= p, n /= p;
            num_factors++;
        }
    if (n > 1)
        factor[num_factors++] = n;
}

/* Determine minimal sum of two factors that are prime between themselves */
unsigned int obtain_minimal_sum() {
    unsigned int i, sum;
    for (i = sum = 0; i < num_factors; i++)
        sum += factor[i];
    if (num_factors == 1)
        sum++;
    else if (num_factors == 0)
        return 2; /* number == 1 */
    return sum;
}

/* Main function */
int main() {
    int n, test = 0;
    compute_primes();
    while (scanf("%d", &n) == 1 && n > 0) {
        decompose(n);
        printf("Case %d: %u\n", ++test, obtain_minimal_sum());
    }
    return EXIT_SUCCESS;
}
