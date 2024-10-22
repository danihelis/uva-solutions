/* 10948
 * The primary problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000000

int prime[MAX_N], num_primes;

/* Compute primes up to N */
void compute_primes() {
    char composite[MAX_N / 2];
    long i, j;
    memset(composite, 0, MAX_N / 2);
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_N / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (j = n * (long) n; j < MAX_N; j += 2 * n)
                composite[j / 2] = 1;
        }
}

/* Compare */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Find possible sum */
int find_sum(int n) {
    int i = 2;
    if (n % 2 == 0)
        for (i = 0; i < num_primes && prime[i] < n; i++) {
            int diff = n - prime[i];
            if (bsearch(&diff, prime, num_primes, sizeof (int), compare) !=
                    NULL)
                return prime[i];
        }
    i = n - 2;
    return bsearch(&i, prime, num_primes, sizeof (int), compare) == NULL ?
        0 : 2;
}

/* Main function */
int main() {
    int n, p;
    compute_primes();
    while (scanf("%d", &n) != EOF && n > 0) {
        printf("%d:\n", n);
        p = find_sum(n);
        if (p == 0)
            printf("NO WAY!\n");
        else
            printf("%d+%d\n", p, n - p);
    }
    return EXIT_SUCCESS;
}
