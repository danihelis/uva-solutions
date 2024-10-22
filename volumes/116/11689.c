/* 11689
 * Soda Surpler
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
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int e, f, c, bottles, total;
        assert(scanf("%d %d %d", &e, &f, &c) != EOF);
        for (total = 0, bottles = e + f; bottles >= c; ) {
            total += bottles / c;
            bottles = bottles / c + bottles % c;
        }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
