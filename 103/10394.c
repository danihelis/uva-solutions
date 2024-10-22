/* 10394
 * Twin Primes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES  1200000
#define MAX_TWINS   100000

int prime[MAX_PRIMES], twin[MAX_TWINS];
long sq_prime[MAX_PRIMES];
int n, num_primes, num_twins;

/* Compute primes until finding i-th twin */
int compute(int i) {
    int k, p;
    for (; i > num_twins; n += 2) {
        for (k = 0, p = 1; p && k < num_primes && sq_prime[k] <= n; k++)
            p = (n % prime[k] != 0);
        if (p) {
            assert(num_primes < MAX_PRIMES);
            prime[num_primes] = n, sq_prime[num_primes] = n * n;
            if (n - prime[num_primes - 1] == 2)
                twin[num_twins++] = num_primes - 1;
            num_primes++;
        }
    }
    return twin[i - 1];
}

/* Main function */
int main() {
    int i;
    prime[0] = 2, num_primes = 1, n = 3, num_twins = 0;
    while (scanf("%d", &i) != EOF) {
        int pi = compute(i);
        printf("(%d, %d)\n", prime[pi], prime[pi + 1]);
    }
    return EXIT_SUCCESS;
}
