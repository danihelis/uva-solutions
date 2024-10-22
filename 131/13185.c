/* 13185
 * DPA Numbers I
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000

int sum[MAX_N];

/* Compute sum of divisors using sieve */
void compute_divisors() {
    int i, n;
    for (n = 1; n <= MAX_N / 2; n++) {
        for (i = n * 2; i <= MAX_N; i += n) {
            sum[i - 2] += n;
        }
    }
}

/* Main function */
int main() {
    int num_tests, n, divs;
    compute_divisors();
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        assert(scanf("%d", &n) == 1);
        divs = sum[n - 2];
        printf("%s\n", n > divs ? "deficient" : n < divs ? "abundant" : 
                "perfect");
    }
    return EXIT_SUCCESS;
}
