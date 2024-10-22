/* 10852
 * Less Prime
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       5100 /* 10000 */
#define MAX_PRIMES  (MAX_N)

int prime[MAX_PRIMES], num_primes;

/* Compute all primes up to MAX_N */
void compute_primes() {
    char composite[MAX_N / 2];
    int i, j;
    prime[0] = 2, num_primes = 1;
    memset(composite, 0, MAX_N / 2);
    for (i = 1; i < MAX_N / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (j = n * n; j < MAX_N; j += 2 * n)
                composite[j / 2] = 1;
        }
}

/* Find a prime that solves the problem */
int find_prime(int n) {
#if 0
    int i, least, x;
    for (i = least = x = 0; i < num_primes && prime[i] <= n; i++) {
        int p = n / prime[i];
        if (least == 0 || p * prime[i] < least)
            least = p * prime[i], x = prime[i];
    }
    return x;
#endif
    int start = 0, end = num_primes;
    n = n % 2 == 0 ? n / 2 + 1 : (n + 1) / 2;
    while (start < end) {
        int middle = (start + end) / 2;
        if (prime[middle] == n)
            return n;
        else if (n < prime[middle])
            end = middle;
        else
            start = middle + 1;
    }
    return prime[start];
}

/* Main function */
int main() {
    int n;
    compute_primes();
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) == 1)
        printf("%d\n", find_prime(n));
    return EXIT_SUCCESS;
}
