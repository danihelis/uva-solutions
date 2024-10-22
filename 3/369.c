/* 369
 * Combinations
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     100
#define MAX_FACTORS     50

typedef int prime_t[MAX_FACTORS];

prime_t factor;
prime_t number[MAX_NUMBERS];
prime_t factorial[MAX_NUMBERS];
int num_factors;

/* Create table of factors for numbers from 2 to 100 */
void create_factor_table() {
    int i, j;

    num_factors = 0;
    memset(number[0], 0, sizeof (prime_t));
    for (i = 2; i <= MAX_NUMBERS; i++) {
        int is_prime = 1;
        memset(number[i - 1], 0, sizeof (prime_t));
        for (j = 0; j < num_factors; j++) {
            int n = i;
            while (n % factor[j] == 0) {
                is_prime = 0;
                number[i - 1][j]++;
                n /= factor[j];
            }
        }
        if (is_prime) {
            number[i - 1][num_factors] = 1;
            factor[num_factors++] = i;
        }
    }
    assert(num_factors <= MAX_FACTORS);

    memset(factorial[0], 0, sizeof (prime_t));
    for (i = 2; i <= MAX_NUMBERS; i++) {
        memcpy(factorial[i - 1], factorial[i - 2], sizeof (prime_t));
        for (j = 0; j < num_factors && factor[j] <= i; j++) {
            factorial[i - 1][j] += number[i - 1][j];
        }
    }
}

/* Divide a product by a factorial */
void divide(prime_t *p, int f) {
    int i;
    for (i = 0; i < num_factors && factor[i] <= f; i++) {
        (*p)[i] -= factorial[f - 1][i];
        assert((*p)[i] >= 0);
    }
}

/* Main function */
int main() {
    int n, m;
    create_factor_table();
    while (scanf("%d %d", &n, &m) != EOF && (n > 0 && m > 0)) {
        prime_t comb;
        int i, j, result;
        memcpy(comb, factorial[n - 1], sizeof (prime_t));
        divide(&comb, m);
        divide(&comb, (n - m));
        for (result = 1, i = 0; i < num_factors; i++) {
            for (j = 0; j < comb[i]; j++) {
                result *= factor[i];
            }
        }
        printf("%d things taken %d at a time is %d exactly.\n", n, m, result);
    }
    return 0;
}
