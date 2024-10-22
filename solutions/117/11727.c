/* 11727
 * Cost Cutting
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
    int num_tests, test;
    assert(scanf("%d", &num_tests));
    for (test = 1; test <= num_tests; test++) {
        int a, b, c, medium;
        assert(scanf("%d %d %d", &a, &b, &c) != EOF);
        if (a < b) {
            medium = (c < a ? a : b < c ? b : c);
        }
        else {
            medium = (c < b ? b : a < c ? a : c);
        }
        printf("Case %d: %d\n", test, medium);
    }
    return 0;
}
