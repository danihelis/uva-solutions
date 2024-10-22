/* 10300
 * Ecological Premium
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int n, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        long total, area, premium;
        assert(scanf("%d", &n) != EOF);
        for (total = 0; n > 0; n--) {
            assert(scanf("%ld %*d %ld", &area, &premium) != EOF);
            total += area * premium;
        }
        printf("%ld\n", total);
    }
    return 0;
}
