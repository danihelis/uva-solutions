/* 11364
 * Parking
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
        int n, value, max, min;
        assert(scanf("%d", &n) != EOF);
        for (max = -1, min = 1000; n > 0; n--) {
            assert(scanf("%d", &value) != EOF);
            max = value > max ? value : max;
            min = value < min ? value : min;
        }
        printf("%d\n", (max - min) * 2);
    }
    return EXIT_SUCCESS;
}
