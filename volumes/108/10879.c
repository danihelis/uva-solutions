/* 10879
 * Code Refactoring
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define MAX_PRIMES  1000

int prime[MAX_PRIMES], num_primes;

/* Compute all primes up to MAX_N */
void compute_primes() {
    char composite[MAX_N / 2];
    int i, k;
    prime[0] = 2, num_primes = 1;
    memset(composite, 0, MAX_N / 2);
    for (i = 1; i < MAX_N / 2; i++)
        if (!composite[i]) {
            int n = 2 * i + 1;
            prime[num_primes++] = n;
            for (k = n * n; k < MAX_N; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Get a factor from n */
int get_factor(int n) {
    int i;
    for (i = 0; i < num_primes; i++)
        if (n % prime[i] == 0)
            return prime[i];
    return n;
}

/* Main function */
int main() {
    int test, num_tests;
    compute_primes();
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int n, a, b, c;
        assert(scanf("%d", &n) == 1);
        a = get_factor(n);
        b = n / a;
        printf("Case #%d: %d = %d * %d", test, n, a, b);
        c = get_factor(b);
        printf(" = %d * %d\n", c * a, b / c);
    }
    return EXIT_SUCCESS;
}
