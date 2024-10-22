/* 11582
 * Colossal Fibonacci Numbers!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000
#define MAX_P   (7 * MAX_N)

int fibonacci[MAX_N][MAX_P], period[MAX_N];

/* Let F(i) be the i-th Fibonacci number. Then
 *      F(i) % n = F(i % P(n)) % P(n)
 * where P(n) is the Pisano period. The sequence F(i) % n repeats itself
 * every P(n) numbers. Note that:
 *      F(i) % n = ( 0 1 ... 1 )*
 * Thus, the sequence [1 | 0] marks the end and beginning of a cycle.
 */
void compute_pisano_period(int n) {
    int i, *series = fibonacci[n - 1];
    series[0] = 0, series[1] = 1;
    for (i = 2; series[i - 1] != 0 || series[i - 2] != 1; i++) {
        series[i] = (series[i - 1] + series[i - 2]) % n;
    }
    period[n - 1] = i - 1;
}

/* Compute a^b mod n */
int exp_mod(unsigned long a, unsigned long b, int n) {
    int r = 1;
    a %= n;
    while (b > 0) {
        if (b & 1) r = (r * a) % n;
        a = (a * a) % n;
        b >>= 1;
    }
    return r;
}

/* Main function */
int main() {
    unsigned long a, b;
    int i, p, n, num_tests;
    memset(period, 0, sizeof (period));
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        assert(scanf("%lu %lu %d", &a, &b, &n) == 3);
        if (n == 1) printf("0\n");
        else {
            if (period[n - 1] == 0) compute_pisano_period(n);
            p = period[n - 1];
            i = exp_mod(a, b, p);
            printf("%d\n", fibonacci[n - 1][i]);
        }
    }
    return EXIT_SUCCESS;
}
