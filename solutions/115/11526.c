/* 11526
 * H(n)
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        long i, n, last, res;
        assert(scanf("%ld", &n) != EOF);
        for (i = 1, last = n, res = 0; i <= last; i++) {
            int div = n / i;
            res += div + (last - MAX(i, div)) * (i - 1);
            last = div;
        }
        printf("%ld\n", res);
    }
    return EXIT_SUCCESS;
}
