/* 160
 * Factors and Factorials
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

/* Main function */
int main() {
    int i, n;
    create_factor_table();
    while (scanf("%d", &n) != EOF && n > 0) {
        prime_t *p = &factorial[n - 1];
        printf("%3d! =", n);
        for (i = 0; i < num_factors && (*p)[i] > 0; i++) {
            if (i > 0 && i % 15 == 0) {
                printf("\n%6s", "");
            }
            printf("%3d", (*p)[i]);
        }
        printf("\n");
    }
    return 0;
}
