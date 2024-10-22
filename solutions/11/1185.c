/* 1185
 * Big Number
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000000

/* Main function */
int main() {
    int n, *digits = malloc(MAX_N * sizeof (int));
    double sum;
    for (n = 2, sum = 0; n <= MAX_N; n++) {
        sum += log10(n);
        digits[n - 1] = ceil(sum);
    }
    digits[0] = 1;
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) == 1)
        printf("%d\n", digits[n - 1]);
    free(digits);
    return EXIT_SUCCESS;
}
