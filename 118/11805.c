/* 11805
 * Bafana Bafana
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
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int n, k, p, r;
        assert(scanf("%d %d %d", &n, &k, &p) != EOF);
        r = (k - 1 + p + n) % n + 1;
        printf("Case %d: %d\n", test, r);
    }
    return EXIT_SUCCESS;
}
