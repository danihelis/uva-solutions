/* 1210
 * Sum of Consecutive Prime Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

int prime[MAX_N], num_primes;
int sums[MAX_N];

/* Compute prime numbers */
void compute_primes() {
    char composite[MAX_N / 2];
    int i, k;
    prime[0] = 2, num_primes = 1;
    memset(composite, 0, MAX_N / 2);
    for (i = 1; i < MAX_N / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (k = n * n; k < MAX_N; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Compute different sums */
void compute_sums() {
    int i, j, sum;
    memset(sums, 0, MAX_N * sizeof (int));
    for (i = 0; i < num_primes; i++)
        for (j = i, sum = 0; j < num_primes && sum < MAX_N; j++) {
            sum += prime[j];
            if (sum < MAX_N)
                sums[sum - 1]++;
        }
}

/* Main function */
int main() {
    int n;
    compute_primes();
    compute_sums();
    while (scanf("%d", &n) != EOF && n > 0)
        printf("%d\n", sums[n - 1]);
    return EXIT_SUCCESS;
}
