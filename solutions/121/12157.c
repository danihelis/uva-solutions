/* 12157
 * Tariff Plan
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
    for (test = 1; test <= num_tests; test++) {
        int c1, c2, n, v;
        assert(scanf("%d", &n) != EOF);
        for (c1 = c2 = 0; n > 0; n--) {
            assert(scanf("%d", &v) != EOF);
            c1 += (v + 30) / 30 * 10;
            c2 += (v + 60) / 60 * 15;
        }
        printf("Case %d: %s%s%s %d\n", test, c1 <= c2 ? "Mile" : "",
                c1 == c2 ? " " : "", c2 <= c1 ? "Juice" : "",
                c1 <= c2 ? c1 : c2);
    }
    return EXIT_SUCCESS;
}
