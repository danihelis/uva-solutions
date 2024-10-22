/* 12149
 * Feynman
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
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int sum = n * (n + 1) * (2 * n + 1) / 6;
        printf("%d\n", sum);
    }
    return EXIT_SUCCESS;
}
