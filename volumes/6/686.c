/* 686
 * Goldbach's Conjecture (II)
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME      33000
#define MAX_NUM_PRIMES  (MAX_PRIME / 5)

int prime[MAX_NUM_PRIMES], num_primes;

#define SQ(x)           ((x) * (x))

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Find all primes upto MAX_PRIME */
void find_primes() {
    int i, k, p;
    prime[0] = 2, num_primes = 1;
    for (i = 3; i < MAX_PRIME; i += 2) {
        for (p = 1, k = 0; p && k < num_primes && SQ(prime[k]) <= i; k++) {
            p = i % prime[k] != 0;
        }
        if (p) {
            prime[num_primes++] = i;
        }
    }
}

/* Find number of pairs whose sum is N */
int find_pairs(int n) {
    int total, p, comp;
    for (total = 0, p = 0; p < num_primes && 2 * prime[p] <= n; p++) {
        comp = n - prime[p];
        total += bsearch(&comp, prime, num_primes, sizeof (int), compare) != NULL ? 1 : 0;
    }
    return total;
}

/* Main function */
int main() {
    int number;
    find_primes();
    while (scanf("%d", &number) != EOF && number > 0) {
        printf("%d\n", find_pairs(number));
    }
    return 0;
}
