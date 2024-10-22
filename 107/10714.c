/* 10714
 * Ants
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN(x, y)   ((x) < (y) ? (x) : (y))
#define MAX(x, y)   ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int n, d, a, min, max;
        assert(scanf("%d %d", &d, &n) == 2);
        for (min = max = 0; n > 0; n--) {
            assert(scanf("%d", &a) == 1);
            min = MAX(min, MIN(d - a, a));
            max = MAX(max, MAX(d - a, a));
        }
        printf("%d %d\n", min, max);
    }
    return EXIT_SUCCESS;
}
