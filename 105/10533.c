/* 10533
 * Digit Primes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 1000000
#define MAX_PRIMES  100000

int prime[MAX_PRIMES];
int num_primes;
int total_digit_prime[MAX_NUMBERS];
int last;


/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Update upper limit of primes */
void update_primes(int top) {
    int n, i;
    for (n = last + 1; n <= top; n++) {
        int is_prime = 1, stop = (int) sqrt(n) + 1;
        for (i = 0; is_prime && i < num_primes && prime[i] <= stop; i++) {
            is_prime = (n % prime[i] != 0);
        }
        total_digit_prime[n - 1] = total_digit_prime[n - 2];
        if (is_prime) {
            int sum = 0, d = n;
            prime[num_primes] = n;
            num_primes++;
            while (d > 0) {
                sum += (d % 10);
                d /= 10;
            }
            total_digit_prime[n - 1] += (bsearch(&sum, prime, num_primes, sizeof (int), compare) !=
                    NULL ? 1 : 0);
            assert(num_primes < MAX_PRIMES);
        }
    }
    if (top > last) {
        last = top;
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    num_primes = 0;
    total_digit_prime[0] = 0;
    last = 1;
    for (; num_tests > 0; num_tests--) {
        int low, high;
        assert(scanf("%d %d", &low, &high) != EOF);
        update_primes(high);
        printf("%d\n", total_digit_prime[high - 1] - (low <= 1 ? 0 : total_digit_prime[low - 2]));
    }    
    return 0;
}
