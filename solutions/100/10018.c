/* 10018
 * Reverse and Add
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Compute the reverse of a number */
long reverse(long n) {
    long r = 0;
    while (n > 0) {
        r = r * 10 + (n % 10);
        n /= 10;
    }
    return r;
}

/* Main function */
int main() {
    int i, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        long n, rev;
        assert(scanf("%ld", &n) != EOF);
        for (i = 0, rev = reverse(n); n != rev; i++) {
            n += rev;
            rev = reverse(n);
        }
        printf("%d %ld\n", i, n);
    }
    return 0;
}
