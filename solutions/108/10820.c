/* 10820
 * Send a Table
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50000
#define MAX_PRIME   224

int num_primes, prime[MAX_PRIME];
long pairs[MAX_N];

/* Compute prime numbers */
void compute_primes() {
    int i, k;
    char composite[MAX_PRIME];
    memset(composite, 0, MAX_PRIME);
    prime[0] = 2, num_primes = 1;
    for (i = 1; i * 2 < MAX_PRIME; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (k = n * n; k < MAX_PRIME; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Totient function: number of relative primes to N in range 1..N */
int totient(int n) {
    int i, phi = 1;
    for (i = 0; i < num_primes && prime[i] * prime[i] <= n; i++) {
        int pk = 1;
        while (n % prime[i] == 0)
            pk *= prime[i], n /= prime[i];
        if (pk > 1)
            phi *= pk - pk / prime[i];
    }
    if (n > 1)
        phi *= n - 1;
    return phi;
}

/* Compute number of pairs */
void compute_table() {
    int i;
    compute_primes();
    pairs[0] = 1;
    for (i = 2; i <= MAX_N; i++)
        pairs[i - 1] = pairs[i - 2] + 2 * totient(i);
}

/* Main function */
int main() {
    int n;
    compute_table();
    while (scanf("%d", &n) == 1 && n > 0)
        printf("%ld\n", pairs[n - 1]);
    return EXIT_SUCCESS;
}
