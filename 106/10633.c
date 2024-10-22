/* 10633
 * Rare Easy Problem
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
    long a, n;
    while (scanf("%ld", &a) != EOF && a > 0) {
        n = a + a / 9;
        if (a % 9 == 0)
            printf("%ld ", n - 1);
        printf("%ld\n", n);
    }
    return EXIT_SUCCESS;
}
