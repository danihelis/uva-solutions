/* 846
 * Steps
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
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int a, b, k, n, r, diff;
        assert(scanf("%d %d", &a, &b) != EOF);
        k = b - a;
        if (k == 0) {
            printf("0\n");
            continue;
        }
        n = sqrt(k);
        diff = k - n * n;
        r = 2 * n - 1 + diff / n + (diff % n > 0 ? 1 : 0);
        printf("%d\n", r);
    }
    return EXIT_SUCCESS;
}
