/* 10200
 * Prime Time
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME   10010

long prime[MAX_PRIME], sq_prime[MAX_PRIME];
int num_primes;
int count[MAX_PRIME];

/* Compute prime numbers */
void compute_primes() {
    char composite[MAX_PRIME / 2];
    int i, k;
    memset(composite, 0, MAX_PRIME / 2);
    prime[0] = 2, sq_prime[0] = 4, num_primes = 1;
    for (i = 1; i < MAX_PRIME / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes]= n, sq_prime[num_primes] = n * n;
            num_primes++;
            for (k = n * n; k < MAX_PRIME; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Compare two integers */
int compare(const void *a, const void *b) {
    return * (long *) a - * (long *) b;
}

/* Is prime? */
int is_prime(long n) {
    int i;
    assert(n > 0);
    if (n <= prime[num_primes - 1])
        return bsearch(&n, prime, num_primes, sizeof (long), compare) != NULL;
    for (i = 0; i < num_primes && sq_prime[i] <= n; i++)
        if (n % prime[i] == 0)
            return 0;
    return 1;
}

/* Main function */
int main() {
    long i;
    int a, b;
    compute_primes();
    count[0] = is_prime(41) ? 1 : 0;
    for (i = 1; i < MAX_PRIME; i++)
        count[i] = count[i - 1] + (is_prime(i * i + i + 41) ? 1 : 0);
    while (scanf("%d %d", &a, &b) == 2) {
        int p = count[b] - (a > 0 ? count[a - 1] : 0),
            q = b - a + 1;
        printf("%.2f\n", (p * 100.0 + 0.0049) / (double) q);
    }
    return EXIT_SUCCESS;
}
