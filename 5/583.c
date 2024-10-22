/* 583
 * Prime Factors
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME       46341
#define MAX_NUM_PRIMES  (MAX_PRIME / 5)
#define SQ(x)           ((x) * (x))

int prime[MAX_NUM_PRIMES], square[MAX_NUM_PRIMES], num_primes, last_unchecked;

/* Compute up to N prime numbers */
void compute_primes(int n) {
    for (; last_unchecked <= n && last_unchecked < MAX_PRIME; last_unchecked += 2) {
        int i, p, k;
        for (i = 0, p = 1, k = last_unchecked; p && i < num_primes && square[i] <= k; i++) {
            p = k % prime[i] != 0;
        }
        if (p) {
            prime[num_primes] = k, square[num_primes] = k * k;
            num_primes++;
        }
    }
}

/* Print factor decomposition */
void print_decomposition(int n) {
    int i, first = 1;
    printf("%d =", n);
    if (n < 0) {
        printf(" -1");
        n *= -1, first = 0;
    }
    for (i = 0; n > 1 && i < num_primes; i++) {
        while (n % prime[i] == 0) {
            printf("%s %d", first ? "" : " x", prime[i]);
            n /= prime[i], first = 0;
        }
    }
    if (n > 1) {
        printf("%s %d", first ? "" : " x", n);
    }
    printf("\n");
}

/* Main function */
int main() {
    int n;
    prime[0] = 2, square[0] = 4, num_primes = 1, last_unchecked = 3;
    while (scanf("%d", &n) != EOF && n != 0) {
        compute_primes(n < 0 ? -n : n);
        print_decomposition(n);
    }
    return 0;
}
