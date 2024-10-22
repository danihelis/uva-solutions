/* 392
 * Polynomial Showdown
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
    while (!feof(stdin)) {
        int k, c, first;
        for (k = 8, first = 1; k >= 0; k--) {
            assert(scanf("%d ", &c) == 1);
            if (c == 0)
                continue;
            (first ? printf("%s", c > 0 ? "" : "-") : 
                     printf(" %c ", c > 0 ? '+' : '-'));
            (abs(c) == 1 && k > 0 ? 0 : printf("%d", abs(c)));
            (k == 0 ? 0 : k == 1 ? printf("x") : printf("x^%d", k));
            first = 0;
        }
        if (first)
            printf("0");
        printf("\n");
    }
    return EXIT_SUCCESS;
}
