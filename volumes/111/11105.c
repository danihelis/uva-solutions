/* 11105
 * Semi-prime H-numbers
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H           1000001
#define MAX_NUMBERS     250001
#define SQRT_MAX_N      500

#define MULT(i,j)       (4 * (i) * (j) + (i) + (j))

int composite[MAX_NUMBERS][2];
char is_prime[MAX_NUMBERS];
int count[MAX_NUMBERS];


/* Find all H-numbers primes abd composites and count semi-primes */
void compute_semi_primes() {
    long i, j;

    for (i = 1; i < MAX_NUMBERS; i++) {
        composite[i][0] = composite[i][1] = 0;
        is_prime[i] = 1;
    }

    for (i = 1; i <= SQRT_MAX_N; i++) {
        if (!is_prime[i]) continue;

        for (j = i; j < MAX_NUMBERS; j++) {
            long m = MULT(i, j);
            if (m >= MAX_NUMBERS) break;

            composite[m][0] = i;
            composite[m][1] = j;
            is_prime[m] = 0;
        }
    }

    count[0] = 0;
    for (i = 1; i < MAX_NUMBERS; i++) {
        char semi_prime = !is_prime[i] && is_prime[composite[i][0]] &&
            is_prime[composite[i][1]];
        count[i] = count[i - 1] + (semi_prime ? 1 : 0);
    }
}

/* Main function */
int main() {
    int n;

    compute_semi_primes();
    while (scanf("%d", &n) == 1 && n > 0) {
        assert(n <= MAX_H);
        printf("%d %d\n", n, count[(n - 1) >> 2]);
    }

    return EXIT_SUCCESS;
}
