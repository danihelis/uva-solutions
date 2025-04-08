/* 10918
 * Tri Tiling
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N   30

int f[MAX_N + 1];

/* Pre-compute all combinations. Let F(n) be the tiliing for n columns,
 * and H(n) the tiling when 1st column has only two rows.
 *
 * F(n) = 0                 if n is odd
 *        1                 if n = 0
 *        2·F(n-2) + H(n-1) otherwise
 *
 * H(n) = 0                 if n is even
 *        1                 if n == 0
 *        F(n-1) + H(n-2)   otherwise
 */
void pre_compute() {
    int i, h[MAX_N + 1];
    f[0] = 1, f[1] = 0;
    h[0] = 0, h[1] = 1;
    for (i = 2; i <= MAX_N; i++) {
        f[i] = 2 * h[i - 1] + f[i - 2];
        h[i] = f[i - 1] + h[i - 2];
    }
}

/* Main function */
int main() {
    int n;
    pre_compute();
    while (scanf("%d", &n) == 1 && n != -1) {
        assert(n <= MAX_N);
        printf("%d\n", f[n]);
    }
    return EXIT_SUCCESS;
}
