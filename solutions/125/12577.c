/* 12577
 * Hajj-e-Akbar
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
    int test = 0;
    char which;
    while (scanf(" %c%*[^\n]", &which) != EOF && which != '*')
        printf("Case %d: Hajj-e-%s\n", ++test, which == 'H' ? "Akbar" :
                "Asghar");
    return EXIT_SUCCESS;
}
