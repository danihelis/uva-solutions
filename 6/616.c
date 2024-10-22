/* 616
 * Coconuts, Revisited
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   9
int limit[MAX_N];

/* Divide coconuts in N stashes plus one */
int divide(int total, int n) {
    int k;
    for (k = 0; k < n; k++) {
        if (--total % n != 0)
            return 0;
        total -= total / n;
    }
    return total % n == 0;
}


/* Main function */
int main() {
    int n, i, found;
    for (n = 2; n <= MAX_N; n++) {
        for (limit[n - 1] = 1, i = n; i > 0; limit[n - 1] *= n, i--)
            ;
        limit[n - 1] -= n; /* N people implies at least N^N-N+1 coconuts */
    }
    while (scanf("%d", &n) != EOF && n >= 0) {
        printf("%d coconuts, ", n);
        for (i = MAX_N, found = 0; !found && i >= 2; i--)
            if (n > limit[i - 1] && divide(n, i)) {
                printf("%d people and 1 monkey\n", i);
                found = 1;
            }
        if (!found)
            printf("no solution\n");
    }
    return EXIT_SUCCESS;
}
