/* 12004
 * Bubble Sort
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
        long n, res;
        assert(scanf("%ld", &n) != EOF);
        res = n * (n - 1) / 2;
        printf("Case %d: ", test);
        (res % 2 == 0 ? printf("%ld\n", res / 2) : printf("%ld/2\n", res));
    }
    return EXIT_SUCCESS;
}
