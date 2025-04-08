/* 12708
 * GCD The Largest
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        long n;
        assert(scanf("%ld", &n) == 1);
        printf("%ld\n", n / 2);
    }
    return EXIT_SUCCESS;
}
