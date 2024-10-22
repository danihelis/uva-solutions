/* 11426
 * GCD - Extreme (II)
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       4000000

unsigned long *g, *phi;

/* Compute G(n) = sum [i=1..n-1, j=i+1..n] gcd(i,j)
 *
 * G(n) = sum [i=2..n] S(i), where S(n) = sum[i=1..n-1] gcd(i, n)
 * S(n) = sum[d|n] phi(d)·(n/d)
 */
void compute_all() {
    unsigned long i, j, k;
    g = (unsigned long *) calloc(MAX_N, sizeof (unsigned long));
    phi = (unsigned long *) calloc(MAX_N, sizeof (unsigned long));
    for (i = 2; i <= MAX_N; i++) {
        int tot = i - 1 + phi[i - 1];
        g[i - 1] += g[i - 2];
        for (j = i, k = tot; j <= MAX_N; j += i, k += tot) {
            g[j - 1] += k;
            phi[j - 1] -= tot;
        }
    }
}

/* Main function */
int main() {
    int n;
    compute_all();
    while (scanf("%d", &n) != EOF && n > 0) {
        assert(n > 1);
        printf("%ld\n", g[n - 1]);
    }
    free(g), free(phi);
    return EXIT_SUCCESS;
}
