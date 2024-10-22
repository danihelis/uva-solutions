/* 12893
 * Count It
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Return computed value: t(n) = t(n/2) + n % 2 */
long t(long n) {
    return (n > 1 ? t(n / 2) : 0) + n % 2;
}

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    while (tests-- > 0) {
        long n;
        assert(scanf("%ld", &n) != EOF);
        printf("%ld\n", t(n));
    }
    return EXIT_SUCCESS;
}
