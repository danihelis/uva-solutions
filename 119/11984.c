/* 11984
 * A Change in Thermal Unit
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
        double temp, inc;
        assert(scanf("%lf %lf", &temp, &inc) != EOF);
        temp += inc * 5 / 9;
        printf("Case %d: %.2f\n", test, temp);
    }
    return EXIT_SUCCESS;
}
