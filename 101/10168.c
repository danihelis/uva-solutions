/* 10168
 * Summation of Four Primes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_P   3162

int prime[MAX_P], num_primes;

/* Compare two integers */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Compute primes */
void compute_primes() {
    char composite[MAX_P / 2];
    int i, k;
    memset(composite, 0, sizeof (composite));
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_P / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (k = n * n; k < MAX_P; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Is prime? */
int is_prime(int n) {
    if (n < MAX_P)
        return bsearch(&n, prime, num_primes, sizeof (int), compare) != NULL;
    else {
        int i;
        for (i = 0; i < num_primes; i++)
            if (n % prime[i] == 0)
                return 0;
        return 1;
    }
}

/* Find sum of two primes */
int find_sum(int n, int *a, int *b) {
    int i;
    for (i = 0; i < num_primes; i++)
        if (is_prime(n - prime[i])) {
            *a = prime[i], *b = n - prime[i];
            return 1;
        }
    return 0;
}

/* Main function */
int main() {
    int n;
    compute_primes();
    while (scanf("%d", &n) != EOF) {
        if (n < 8)
            printf("Impossible.\n");
        else {
            int a, b;
            printf("2 %d ", n % 2 == 0 ? 2 : 3);
            n -= n % 2 == 0 ? 4 : 5;
            assert(find_sum(n, &a, &b));
            printf("%d %d\n", a, b);
        }
    }
    return EXIT_SUCCESS;
}
