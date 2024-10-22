/* 10919
 * Prerequisites?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

/* Main function */
int main() {
    char course[MAX_N];
    int i, k, m, c, r, fulfil;
    while (scanf("%d %d", &k, &m) == 2) {
        memset(course, 0, MAX_N);
        for (i = 0; i < k; i++) {
            assert(scanf("%d", &c) == 1);
            course[c] = 1;
        }
        for (i = 0, fulfil = 1; i < m; i++) {
            assert(scanf("%d %d", &k, &r) == 2);
            for (; k > 0; k--) {
                assert(scanf("%d", &c) == 1);
                r -= course[c] ? 1 : 0;
            }
            fulfil &= r <= 0;
        }
        puts(fulfil ? "yes" : "no");
    }
    return EXIT_SUCCESS;
}
