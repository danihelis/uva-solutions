/* 11661
 * Burger Time?
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
    int len;
    while (scanf("%d", &len) != EOF && len > 0) {
        char what, last;
        int dist, best;
        for (best = 1 << 30, dist = 0, last = 0; len > 0; len--) {
            assert(scanf(" %c", &what) != EOF);
            if (best > 0) {
                dist++;
                if (what == 'Z')
                    best = 0;
                else if (what == 'R' || what == 'D') {
                    if (what != last && last != 0 && best > dist)
                        best = dist;
                    dist = 0;
                    last = what;
                }
            }
        }
        printf("%d\n", best);
    }
    return EXIT_SUCCESS;
}
