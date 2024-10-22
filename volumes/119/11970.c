/* 11970
 * Lucky Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int x, n, k;
        assert(scanf("%d", &n) == 1);
        printf("Case %d:", test);
        for (k = sqrt(n); k >= 1; k--) {
            x = n - k * k;
            if (x > 0 && x % k == 0) printf(" %d", x);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
