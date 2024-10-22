/* 13148
 * A Giveaway
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_SOLS    21
const int solution[] = {1, 64, 729, 4096, 15625, 46656, 117649, 262144, 
    531441, 1000000, 1771561, 2985984, 4826809, 7529536, 11390625, 16777216, 
    24137569, 34012224, 47045881, 64000000, 85766121};

/* Compare */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0)
        printf("%s\n", bsearch(&n, solution, NUM_SOLS, sizeof (int), compare)
                == NULL ? "Ordinary" : "Special");
    return EXIT_SUCCESS;
}
