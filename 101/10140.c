/* 10140
 * Prime Distance
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50000
#define MAX_PRIMES  10000

int primes[MAX_PRIMES];
long sq_primes[MAX_PRIMES];
int num_primes;

/* Compute prime numbers */
void compute_primes() {
    char is_prime[MAX_N / 2];
    long n, m;
    memset(is_prime, 1, MAX_N / 2);
    primes[0] = 2, sq_primes[0] = 4, num_primes = 1;
    for (n = 3; n < MAX_N; n += 2)
        if (is_prime[n / 2]) {
            primes[num_primes] = n;
            sq_primes[num_primes] = n * n;
            num_primes++;
            for (m = n * n; m < MAX_N; m += 2 * n)
                is_prime[m / 2] = 0;
        }
}

/* Check if is prime */
char is_prime(int n) {
    int i;
    for (i = 0; sq_primes[i] <= n && i < num_primes; i++)
        if (n % primes[i] == 0)
            return 0;
    return n > 1 ? 1 : 0;
}

/* Main function */
int main() {
    int low, high;
    compute_primes();
    while (scanf("%d %d", &low, &high) != EOF) {
        int n, last, c1, c2, c_diff, d1, d2, d_diff;
        c1 = c2 = d1 = d2 = c_diff = d_diff = last = -1;
        for (n = low; n <= high; n++)
            if (is_prime(n)) {
                if (last != -1) {
                    int diff = n - last;
                    if (c_diff == -1 || diff < c_diff)
                        c1 = last, c2 = n, c_diff = diff;
                    if (d_diff == -1 || diff > d_diff)
                        d1 = last, d2 = n, d_diff = diff;
                }
                last = n;
            }
        if (c_diff == -1)
            printf("There are no adjacent primes.\n");
        else
            printf("%d,%d are closest, %d,%d are most distant.\n",
                    c1, c2, d1, d2);
    }
    return EXIT_SUCCESS;
}
