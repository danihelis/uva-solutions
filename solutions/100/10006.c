/* 10006
 * Carmichael Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_CARMICHAEL  15

int carmichael[NUM_CARMICHAEL] = {
    561, 1105, 1729, 2465, 2821,
    6601, 8911, 10585, 15841, 29341,
    41041, 46657, 52633, 62745, 63973};

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        if (bsearch(&n, carmichael, NUM_CARMICHAEL, sizeof (int), compare) == NULL) {
            printf("%d is normal.\n", n);
        }
        else {
            printf("The number %d is a Carmichael number.\n", n);
        }
    }
    return 0;
}
