/* 1213
 * Sum of Different Primes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1120
#define MAX_K   14

int table[MAX_N][MAX_K];
int prime[MAX_N], num_primes;

/* Compute primes */
void compute_primes() {
    char composite[MAX_N / 2];
    int i, n, k;
    memset(composite, 0, MAX_N / 2);
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_N / 2; i++)
        if (!composite[i]) {
            n = 2 * i + 1;
            prime[num_primes++] = n;
            for (k = n * n; k <= MAX_N; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Compute sets of different number primes sum:
        s[n,k] = SUM_p{ s[n-p,k-1] + 1 }, for p prime
*/
void compute_table() {
    int n, k, i;
    memset(table, 0, MAX_N * MAX_K * sizeof (int));
    for (i = 0; i < num_primes; i++) {
        int p = prime[i];
        for (k = MAX_K; k > 1; k--)
            for (n = 2; n <= MAX_N - p; n++)
                if (table[n - 1][k - 2] > 0)
                    table[n + p - 1][k - 1] += table[n - 1][k - 2];
        table[p - 1][0] = 1;
    }
}

/* Main function */
int main() {
    int n, k;
    compute_primes();
    compute_table();
    while (scanf("%d %d", &n, &k) == 2 && n > 0)
        printf("%d\n", table[n - 1][k - 1]);
    return EXIT_SUCCESS;
}
