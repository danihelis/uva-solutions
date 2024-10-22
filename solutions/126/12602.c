/* 12602
 * Nice Licence Plates
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
        char letter[5], *c;
        int alpha, number;
        assert(scanf(" %3s-%d", letter, &number) == 2);
        for (c = letter, alpha = 0; *c != 0; c++)
            alpha = alpha * 26 + toupper(*c) - 'A';
        printf("%snice\n", abs(alpha - number) <= 100 ? "" : "not ");
    }
    return EXIT_SUCCESS;
}
