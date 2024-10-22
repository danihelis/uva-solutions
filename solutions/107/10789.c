/* 10789
 * Prime Frequency
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME       2010
#define TOTAL_DIGIT     10
#define TOTAL_UPPER     (TOTAL_DIGIT + 26)
#define TOTAL_ALL       (TOTAL_UPPER + 26)

int prime[MAX_PRIME], num_primes;

#define SQ(x)           ((x) * (x))

/* Compute all prime numbers up to MAX_PRIME */
void compute_prime() {
    int i, k, p;
    prime[0] = 2, num_primes = 1;
    for (i = 3; i < MAX_PRIME; i += 2) {
        for (k = 0, p = 1; p && SQ(prime[k]) <= i; k++) {
            p = i % prime[k] != 0;
        }
        if (p) {
            prime[num_primes++] = i;
        }
    }
}

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    int test, num_tests;
    compute_prime();
    assert(scanf("%d ", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, count[TOTAL_ALL];
        char symbol, any;
        memset(count, 0, TOTAL_ALL * sizeof (int));
        while (scanf("%c", &symbol) != EOF && symbol != '\n') {
            int index = isdigit(symbol) ? symbol - '0' : 
                isupper(symbol) ? TOTAL_DIGIT + symbol - 'A' : TOTAL_UPPER + symbol - 'a';
            count[index]++;
        }
        printf("Case %d: ", test);
        for (i = 0, any = 0; i < TOTAL_ALL; i++) {
            if (bsearch(&count[i], prime, num_primes, sizeof (int), compare) != NULL) {
                printf("%c", i < TOTAL_DIGIT ? i + '0' : i < TOTAL_UPPER ? i - TOTAL_DIGIT + 'A' :
                        i - TOTAL_UPPER + 'a');
                any = 1;
            }
        }
        printf("%s\n", any ? "" : "empty");
    }
    return 0;
}
