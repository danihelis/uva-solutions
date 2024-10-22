/* 11310
 * Delivery Debacle
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   40

/* Main function */
int main() {
    long comb[MAX_N];
    int n;
    comb[0] = 1;
    for (n = 1; n <= MAX_N; n++)
        comb[n] = comb[n - 1] 
            + (n >= 2 ? 4 * comb[n - 2] : 0)
            + (n >= 3 ? 2 * comb[n - 3] : 0);
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) != EOF) {
        printf("%ld\n", comb[n]);
    }
    return EXIT_SUCCESS;
}
