/* 10963
 * The Swallowing Ground
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
    assert(scanf("%d", &num_tests) != 0);
    for (; num_tests > 0; num_tests--) {
        int n, a, b, can, gap;
        assert(scanf("%d %d %d", &n, &a, &b) == 3);
        gap = a - b, can = 1;
        for (; n > 1; n--) {
            assert(scanf("%d %d", &a, &b) == 2);
            can &= a - b == gap;
        }
        printf("%s%s\n", can ? "yes" : "no", num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
