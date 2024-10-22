/* 10042
 * Smith Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000000200
#define MAX_SQRT_N  31624   /* sqrt(MAX_N) */
#define MAX_PRIMES  30000

int prime[MAX_PRIMES], num_primes;

/* Compute primes */
void compute_primes() {
    char composite[MAX_SQRT_N / 2];
    int i, n, k, limit;
    for (i = 0; i < MAX_SQRT_N / 2; i++)
        composite[i] = 0;
    prime[0] = 2, num_primes = 1;
    for (i = 1, limit = sqrt(MAX_SQRT_N); i < MAX_SQRT_N / 2; i++)
        if (!composite[i]) {
            n = 2 * i + 1;
            prime[num_primes++] = n;
            if (n <= limit)
                for (k = n * n; k < MAX_SQRT_N; k += 2 * n)
                    composite[k / 2] = 1;
        }
}

/* Sum of digits */
int sum_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

/* Is Smith number? */
int is_smith(int n) {
    int k, start = n, sum = sum_digits(n);
    for (k = 0; sum >= 0 && k < num_primes && n > 1; k++)
        if (start == prime[k])
            return 0;
        else if (n % prime[k] == 0) {
            int psum = sum_digits(prime[k]);
            do {
                sum -= psum;
                n /= prime[k];
            } while (sum >=0 && n % prime[k] == 0);
        }
    if (n > 1 && n != start)
        sum -= sum_digits(n);
    return sum == 0;
}

/* Find Smith number */
void find_smith_number(int start) {
    int n, smith;
    for (n = start + 1, smith = 0; !smith; n++)
        smith = is_smith(n);
    printf("%d\n", n - 1);
}

/* Main function */
int main() {
    int n, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    compute_primes();
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d", &n) != EOF);
        find_smith_number(n);
    }
    return EXIT_SUCCESS;
}
