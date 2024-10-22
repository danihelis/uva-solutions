/* 1644
 * Prime Gap
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME_NUMBER 1300000
#define MAX_PRIMES 100000

int prime[MAX_PRIMES];
int num_primes;

/* Compute primes */
void compute_primes() {
    char composite[MAX_PRIME_NUMBER / 2];
    long i, j, k;
    memset(composite, 0, sizeof (composite));
    prime[0] = 2;
    num_primes = 1;
    for (i = 1, k = 3; num_primes < MAX_PRIMES; i++, k += 2) {
        if (composite[i]) continue;
        prime[num_primes++] = k;
        for (j = k * k / 2; j < MAX_PRIME_NUMBER / 2; j += k) {
            composite[j] = 1;
        }
    }
}

/* Binary search for the lowest prime higher than or equal to value */
int * search_prime(int value) {
    int start = 0, end = num_primes;
    while (start < end) {
        int middle = (start + end) / 2;
        if (prime[middle] == value) return &prime[middle];
        if (value < prime[middle]) end = middle;
        else start = middle + 1;
    }
    return &prime[start];
}

/* Return prime gap */
int prime_gap(int n) {
    int *upper = search_prime(n);
    if (*upper == n) return 0;
    return *upper - *(upper - 1);
}

/* Main function */
int main() {
    int n;
    compute_primes();
    while (scanf("%d", &n) != EOF && n > 0) {
        printf("%d\n", prime_gap(n));
    }
    return EXIT_SUCCESS;
}
