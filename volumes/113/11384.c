/* 11384
 * Help is needed for Dexter
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
    int n, l;
    while (scanf("%d", &n) != EOF) {
        for (l = 0; n > 0; n /= 2, l++)
            ;
        printf("%d\n", l);
    }
    return EXIT_SUCCESS;
}
