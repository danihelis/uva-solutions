/* 10139
 * Factovisors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME  65536
#define MAX_NUM_PRIMES (MAX_PRIME / 2)

int primes[MAX_NUM_PRIMES], num_primes;

/* Compute all prime numbers using seive */
void compute_primes() {
    char composite[MAX_PRIME / 2];
    int i;
    long k;
    primes[0] = 2, num_primes = 1;
    memset(composite, 0, MAX_PRIME / 2);
    for (i = 1; i < MAX_PRIME / 2; i++)
        if (!composite[i]) {
            long prime = i * 2 + 1;
            primes[num_primes++] = prime;
            for (k = prime * prime; k < MAX_PRIME; k += 2 * prime)
                composite[k / 2] = 1;
        }
}

/* Count how many times a prime number occurs on fat */
int count_primes(int prime, int fat) {
    int count = 0;
    long prod = prime;
    while (prod <= fat) {
        count += fat / prod;
        prod *= prime;
    }
    return count;
}

/* Decompose a number in prime values and check whether fat! contains them */
int decompose_and_check(int m, int fat) {
    int i;
    for (i = 0; m > 1 && i < num_primes; i++) {
        int count = 0, prime = primes[i];
        while (m % prime == 0) {
            count++;
            m /= prime;
        }
        if (count > 0 && count > count_primes(prime, fat))
            return 0;
    }
    return m == 1 || count_primes(m, fat) > 0;
}

/* Main function */
int main() {
    int fat, n;
    compute_primes();
    while (scanf("%d %d", &fat, &n) != EOF) {
        printf("%d %s %d!\n", n, decompose_and_check(n, fat) ? "divides" : 
                "does not divide", fat);
    }
    return EXIT_SUCCESS;
}
