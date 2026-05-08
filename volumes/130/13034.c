/* 13034
 * Solve Everything :-)
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, n, all;
        for (i = 0, all = 1; i < 13; i++) {
            assert(scanf("%d", &n) == 1);
            all &= n != 0;
        }
        printf("Set #%d: %s\n", test, all ? "Yes" : "No");
    }
    return EXIT_SUCCESS;
}
