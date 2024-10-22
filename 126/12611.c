/* 12611
 * Beautiful Flag
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
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, height, left, right, radius;
        assert(scanf("%d", &radius) == 1);
        height = radius * 3 / 2;
        left = radius * 9 / 4;
        right = left + radius / 2;
        printf("Case %d:\n", test);
        for (i = 0; i < 4; i++) {
            int x = i % 3 == 0 ? -1 * left : right,
                y = i < 2 ? height : -1 * height;
            printf("%d %d\n", x, y);
        }
    }
    return EXIT_SUCCESS;
}
