/* 10742
 * The New Rule in Euphomia
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N           1000000
#define SQRT_MAX_N      1000
#define MAX_PRIMES      100000

int primes[MAX_PRIMES];
int num_primes;


/* Compute all primes up to MAX_N */
void compute_primes() {
    char composite[MAX_N / 2 + 1];
    int i, j, p;

    memset(composite, 0, sizeof (char) * (MAX_N / 2 + 1));
    primes[0] = 2;
    num_primes = 1;

    for (i = 1; i < MAX_N / 2; i++) {
        if (!composite[i]) {
            p = 2 * i + 1;
            primes[num_primes++] = p;

            if (p < SQRT_MAX_N) {
                for (j = p * p; j <= MAX_N; j += 2 * p) {
                    composite[j / 2] = 1;
                }
            }
        }
    }
}


/* Binary search a prime number which is half a given value */
int bsearch_half(int number) {
    int half = number / 2;
    int start = 0, end = num_primes;

    while (start < end) {
        int middle = (start + end) / 2;
        if (primes[middle] == half) return middle;
        else if (half > primes[middle]) start = middle + 1;
        else end = middle;
    }
    return start - 1;
}


/* Compute all different pairs (X, Y) such that X + Y <= N, with X, Y primes */
long compute_different_pairs(int number) {
    long count = 0;
    int index, i, j;

    if (number < 5) return 0;

    index = bsearch_half(number);
    count += index * (index + 1) / 2; /* all sums up to index */

    for (i = index + 1, j = index; i < num_primes &&
            primes[i] < number && j >= 0; i++) {
        for (; j >= 0 && primes[i] + primes[j] > number; j--)
            ;
        if (j >= 0) count += j + 1;
    }
    return count;
}


/* Main function */
int main() {
    int num_tests = 1, number;

    compute_primes();
    while (scanf("%d", &number) == 1 && number > 0) {
        long result = compute_different_pairs(number);
        printf("Case %d: %ld\n", num_tests++, result);
    }

    return EXIT_SUCCESS;
}
