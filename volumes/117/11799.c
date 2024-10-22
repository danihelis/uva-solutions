/* 11799
 * Horror Dash
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
    int test, num_tests, num_values, value, i, max;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        assert(scanf("%d", &num_values) != EOF);
        for (i = 0, max = 0; i < num_values; i++) {
            assert(scanf("%d", &value) != EOF);
            if (value > max) {
                max = value;
            }
        }
        printf("Case %d: %d\n", test, max);
    }
    return 0;
}
