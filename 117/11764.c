/* 11764
 * Jumping Mario
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
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, n, high, low, last, wall;
        assert(scanf("%d %d", &n, &last) != EOF);
        for (i = 1, high = 0, low = 0; i < n; i++) {
            assert(scanf("%d", &wall) != EOF);
            high += (wall > last ? 1 : 0);
            low += (wall < last ? 1 : 0);
            last = wall;
        }
        printf("Case %d: %d %d\n", test, high, low);
    }
    return 0;
}
