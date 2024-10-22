/* 12751
 * An Interesting Game
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
    int n, k, x, test = 0;
    assert(scanf("%*d") != EOF);
    while (scanf("%d %d %d", &n, &x, &k) == 3)
        printf("Case %d: %d\n", ++test,
                n * (n + 1) / 2 + k * (k - 1) / 2 - (x + k) * (x + k - 1) / 2);
    return EXIT_SUCCESS;
}
