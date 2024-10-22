/* 10784
 * Diagonal
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
    unsigned long n, test = 0;
    while (scanf("%lu", &n) != EOF && n > 0) {
        unsigned long size = ceil((3 + sqrt(9 + 8 * n)) / 2);
        printf("Case %lu: %ld\n", ++test, size);
    }
    return EXIT_SUCCESS;
}
