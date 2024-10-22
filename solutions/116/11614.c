/* 11614
 * Etruscan Warriors Never Play Chess
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
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        long n, k;
        assert(scanf("%ld", &n) != EOF);
        k = (sqrt(1 + 8 * n) - 1) / 2;
        printf("%ld\n", k);
    }
    return EXIT_SUCCESS;
}
