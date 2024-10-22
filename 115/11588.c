/* 11588
 * Image Coding
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       26

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int m, n, r, c, i, max, multi, count[MAX_N], cost;
        char k;
        memset(count, 0, sizeof (count));
        assert(scanf("%d %d %d %d", &r, &c, &m, &n) == 4);
        for (r *= c, i = max = multi = 0; i < r; i++) {
            assert(scanf(" %c", &k) == 1);
            c = k - 'A';
            count[c]++;
            if (count[c] > max)
                max = count[c], multi = 1;
            else if (count[c] == max)
                multi++;
        }
        cost = max * multi * m + (r - max * multi) * n;
        printf("Case %d: %d\n", test, cost);
    }
    return EXIT_SUCCESS;
}
