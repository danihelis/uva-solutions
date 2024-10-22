/* 11388
 * GCD LCM
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
    int g, l;
    assert(scanf("%*d") != EOF);
    while (scanf("%d %d", &g, &l) != EOF) {
        if (l % g == 0)
            printf("%d %d\n", g, l);
        else
            printf("-1\n");
    }
    return EXIT_SUCCESS;
}
