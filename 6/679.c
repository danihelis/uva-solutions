/* 679
 * Dropping Balls
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
        int d, number, position, depth;
        assert(scanf("%d %d", &depth, &position) != EOF);
        for (d = 1, number = 1, position--; d < depth; d++) {
            number = 2 * number + (position % 2 == 0 ? 0 : 1);
            position /= 2;
        }
        printf("%d\n", number);
    }
    return 0;
}
