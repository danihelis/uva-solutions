/* 11889
 * Benefit
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIME   10000

typedef struct {
    int value, power;
} factor_t;

int prime[MAX_PRIME], num_primes;

/* Compute all primes */
void compute_primes() {
    char composite[MAX_PRIME / 2];
    int i, j;
    memset(composite, 0, MAX_PRIME / 2);
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_PRIME / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (j = n * n; j < MAX_PRIME; j += 2 * n)
                composite[j / 2] = 1;
        }
}

/* Obtain prime factors */
void factorize(int n, factor_t factor[], int *num_factors) {
    int i;
    for (i = 0, *num_factors = 0; n > 1 && i < num_primes; i++)
        if (n % prime[i] == 0) {
            factor_t *f = &factor[(*num_factors)++];
            f->value = prime[i], f->power = 0;
            while (n % f->value == 0)
                f->power++, n /= f->value;
        }
    if (n > 1) {
        factor_t *f = &factor[(*num_factors)++];
        f->value = n, f->power = 1;
    }
}

/* Main function */
int main() {
    int num_tests;
    compute_primes();
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int a, c;
        assert(scanf("%d %d", &a, &c) == 2);
        if (c % a != 0)
            printf("NO SOLUTION\n");
        else {
            factor_t fa[MAX_PRIME], fc[MAX_PRIME];
            int na, nc, ia, ic, j, b;
            factorize(a, fa, &na), factorize(c, fc, &nc);
            for (ia = ic = 0, b = 1; ic < nc; ic++) {
                if (ia < na && fa[ia].value == fc[ic].value) {
                    ia++;
                    if (fa[ia - 1].power == fc[ic].power)
                        continue;
                }
                for (j = 0; j < fc[ic].power; j++)
                    b *= fc[ic].value;
            }
            printf("%d\n", b);
        }
    }
    return EXIT_SUCCESS;
}
