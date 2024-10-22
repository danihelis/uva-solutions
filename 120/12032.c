/* 12032
 * The Monkey and the Oiled Bamboo
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int n, max, k, last, val, height;
        assert(scanf("%d", &n) != EOF);
        for (max = 0, k = 0, last = 0; n > 0; n--) {
            assert(scanf("%d", &val) != EOF);
            height = val - last;
            if (height > k) {
                max = MAX(max + 1, height);
                k = max;
            }
            if (height == k)
                k--;
            last = val;
        }
        printf("Case %d: %d\n", test, max);
    }
    return EXIT_SUCCESS;
}
