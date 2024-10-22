/* 991
 * Safe Salutations
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10

/* Main function */
int main() {
    long catalan[MAX_N + 1];
    int n, first = 1;
    catalan[0] = 1;
    for (n = 1; n <= MAX_N; n++)
        catalan[n] = (4 * n - 2) * catalan[n - 1] / (n + 1);
    while (scanf("%d", &n) != EOF) {
        (first ? first = 0 : printf("\n"));
        printf("%ld\n", catalan[n]);
    }
    return EXIT_SUCCESS;
}
