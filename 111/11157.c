/* 11157
 * Dynamic Frog
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       102
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, n, width, maximum, distance[MAX_N];
        char hard[MAX_N], type;
        assert(scanf("%d %d", &n, &width) != EOF);
        distance[0] = 0, distance[n + 1] = width;
        hard[0] = 1, hard[n + 1] = 1;
        for (i = 0; i < n; i++) {
            assert(scanf(" %c-%d", &type, &distance[i + 1]) != EOF);
            hard[i + 1] = type == 'B';
        }
        for (i = 0, maximum = 0; i <= n; i++) {
            if (hard[i] && hard[i + 1])
                width = distance[i + 1] - distance[i];
            else if (!hard[i])
                width = distance[i + 1] - distance[i - 1];
            else
                width = 0;
            maximum = MAX(width, maximum);
        }
        printf("Case %d: %d\n", test, maximum);
    }
    return EXIT_SUCCESS;
}
