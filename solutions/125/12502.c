/* 12502
 * Three Families
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
    int tests, a, b, t;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        int pay;
        assert(scanf("%d %d %d", &a, &b, &t) != EOF);
        pay = a * 3 * t / (a + b) - t;
        printf("%d\n", pay);
    }
    return EXIT_SUCCESS;
}
