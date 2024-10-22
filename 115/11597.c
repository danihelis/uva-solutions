/* 11597
 * Spanning Subtree
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
    int test = 0, n;
    while (scanf("%d", &n) != EOF && n > 0)
        printf("Case %d: %d\n", ++test, n / 2);
    return EXIT_SUCCESS;
}
