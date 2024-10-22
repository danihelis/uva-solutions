/* 10642
 * Can You Solve It?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Compute coordinate */
long coordinate(int x, int y) {
    int n = x + y;
    return n * (n + 1) / 2 + x;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int x1, y1, x2, y2;
        long p1, p2;
        assert(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4);
        p1 = coordinate(x1, y1), p2 = coordinate(x2, y2);
        printf("Case %d: %ld\n", test, p2 - p1);
    }
    return EXIT_SUCCESS;
}
