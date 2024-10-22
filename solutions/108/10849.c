/* 10849
 * Move the bishop
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
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int k, r0, c0, r1, c1;
        assert(scanf("%d %*d", &k) == 1);
        for (; k > 0; k--) {
            assert(scanf("%d %d %d %d", &r0, &c0, &r1, &c1) == 4);
            if (((r0 + c0) % 2) != ((r1 + c1) % 2))
                puts("no move");
            else if (r0 == r1 && c0 == c1)
                puts("0");
            else if (abs(r0 - r1) == abs(c0 - c1))
                puts("1");
            else
                puts("2");
        }
    }
    return EXIT_SUCCESS;
}
