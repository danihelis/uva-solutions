/* 12650
 * Dangerous Dive
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000

/* Main function */
int main() {
    int n, s, i, k;
    while (scanf("%d %d", &n, &s) == 2) {
        char returned[MAX_N];
        memset(returned, 0, n);
        for (i = 0; i < s; i++) {
            assert(scanf("%d", &k) == 1);
            returned[--k] = 1;
        }
        if (n == s)
            puts("*");
        else {
            for (i = 0; i < n; i++)
                if (!returned[i])
                    printf("%d ", i + 1);
            puts("");
        }
    }
    return EXIT_SUCCESS;
}
