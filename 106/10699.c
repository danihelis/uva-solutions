/* 10699
 * Count the factors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES  1000000
#define SQ(x)       ((x) * (x))

int prime[MAX_PRIMES], num_primes, n;

/* Find primes */
void find_primes(int up_to) {
    int k, p;
    for (; n <= up_to; n += 2) {
        for (k = 0, p = 1; p && k < num_primes && SQ(prime[k]) <= n; k++)
            p = (n % prime[k] != 0);
        if (p)
            prime[num_primes++] = n;
    }
}

/* Decompose in prime numbers */
int decompose(int number) {
    int k, factors;
    find_primes(number);
    for (k = 0, factors = 0; k < num_primes && prime[k] <= number; k++) {
        if (number % prime[k] == 0) {
            factors++;
            while (number % prime[k] == 0)
                number /= prime[k];
        }
    }
    return factors;
}

/* Main function */
int main() {
    int number;
    prime[0] = 2, num_primes = 1, n = 3;
    while (scanf("%d", &number) != EOF && number > 0)
        printf("%d : %d\n", number, decompose(number));
    return EXIT_SUCCESS;
}
