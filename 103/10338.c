/* 10338
 * Mischievous Children
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LETTERS     20
#define MAX_STRING      (MAX_LETTERS + 2)

#define NUM_PRIMES      8

typedef int prime_t[NUM_PRIMES];

prime_t primes = {2, 3, 5, 7, 11, 13, 17, 19};
prime_t factors[MAX_LETTERS], factorial[MAX_LETTERS];

/* Compare letters */
int compare(const void *a, const void *b) {
    return * (char *) a - * (char *) b;
}

/* Define factors for numbers 1 to 20 */
void define_factors() {
    int i, p, n;
    memset(factors, 0, MAX_LETTERS * sizeof (prime_t));
    memset(factorial, 0, MAX_LETTERS * sizeof (prime_t));
    for (i = 0; i < MAX_LETTERS; i++) {
        for (p = 0, n = i + 1; p < NUM_PRIMES && primes[p] <= n; p++)
            while (n % primes[p] == 0) {
                factors[i][p]++;
                n /= primes[p];
            }
        if (i > 0)
            for (p = 0; p < NUM_PRIMES; p++)
                factorial[i][p] = factorial[i - 1][p] + factors[i][p];
    }
}

/* Compute combinations */
long combinations(char *word) {
    int p, k, diff, size = strlen(word);
    long result;
    prime_t comb;
    for (p = 0; p < NUM_PRIMES; p++)
        comb[p] = factorial[size - 1][p];
    qsort(word, size, sizeof (char), compare);
    while (*word != 0) {
        char *first = word;
        for (word++; *word != 0 && *word == *first; word++)
            ;
        diff = word - first;
        if (diff > 1)
            for (p = 0; p < NUM_PRIMES; p++)
                comb[p] -= factorial[diff - 1][p];
    }
    for (result = 1, p = 0; p < NUM_PRIMES; p++) {
        assert(comb[p] >= 0);
        for (k = 0; k < comb[p]; k++)
            result *= primes[p];
    }
    return result;
}

/* Main function */
int main() {
    int test, num_tests;
    define_factors();
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        char line[MAX_STRING];
        assert(scanf(" %s", line) != EOF);
        printf("Data set %d: %ld\n", test + 1, combinations(line));
    }
    return EXIT_SUCCESS;
}
