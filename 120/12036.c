/* 12036
 * Stable Grid
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   101

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, j, n, s, v, count[MAX_N];
        memset(count, 0, MAX_N * sizeof (int));
        assert(scanf("%d", &n) == 1);
        for (i = 0, s = 1; i < n; i++)
            for (j = 0; j < n; j++) {
                assert(scanf("%d", &v) == 1);
                s &= ++count[v] <= n;
            }
        printf("Case %d: %s\n", test, s ? "yes" : "no");
    }
    return EXIT_SUCCESS;
}
