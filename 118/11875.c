/* 11875
 * Brick Game
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
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        int i, n, age, middle, captain;
        assert(scanf("%d", &n) != EOF);
        for (i = 0, middle = n / 2, captain = 0; i < n; i++) {
            assert(scanf("%d", &age) != EOF);
            if (i == middle)
                captain = age;
        }
        printf("Case %d: %d\n", test + 1, captain);
    }
    return EXIT_SUCCESS;
}
