/* 12798
 * Handball
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
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        int i, j, goals, scored, total;
        for (i = total = scored = 0; i < n; i++, total += scored ? 1 : 0)
            for (j = 0, scored = 1; j < m; j++) {
                assert(scanf("%d", &goals) == 1);
                scored &= goals > 0;
            }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
