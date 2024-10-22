/* 11743
 * Credit Check
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
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int k, i, n, m, sum;
        for (k = sum = 0; k < 4; k++) {
            assert(scanf("%d", &n) == 1);
            for (i = 0; n > 0; ++i, n /= 10)
                for (m = (n % 10) * (1 + (i % 2)); m > 0; m /= 10)
                    sum += m % 10;
        }
        printf("%salid\n", sum % 10 == 0 ? "V" : "Inv");
    }
    return EXIT_SUCCESS;
}
