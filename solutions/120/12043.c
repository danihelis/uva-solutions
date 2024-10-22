/* 12043
 * Divisors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100000

typedef struct {
    long count, sum;
} divisor_t;

divisor_t divisor[MAX_N];

/* Compute count and sum of divisors of all numbers from 1 to MAX_N */
void compute_divisors() {
    int i, k;
    memset(divisor, 0, MAX_N * sizeof (divisor_t));
    for (i = 1; i <= MAX_N; i++) {
        for (k = i; k <= MAX_N; k += i) {
            divisor_t *d = &divisor[k - 1];
            d->count++, d->sum += i;
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    compute_divisors();
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int i, a, b, k;
        long count, sum;
        assert(scanf("%d %d %d", &a, &b, &k) != EOF);
        for (i = (a + k - 1) / k * k, count = sum = 0; i <= b; i += k) {
            divisor_t *d = &divisor[i - 1];
            count += d->count, sum += d->sum;
        }
        printf("%ld %ld\n", count, sum);
    }
    return EXIT_SUCCESS;
}
