/* 10693
 * Traffic Volume
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* We have:
 *      d = v^2 / 2f
 *      vol = 3600 · v / (L + d)
 *          = 3600 · v / (L + v^2/2f)
 *          = 7200fv / (2fL + v^2)
 *
 * To maximize vol, we compute
 *      d/dv vol = 0
 *      d/dv 7200fv / (2fL + v^2) = 0
 *      d/dv v / (2fL + v^2) = 0
 *      (2fL + v^2) - v·(2v) = 0
 *      v = sqrt(2fL)
 *
 * Thence:
 *      d = 2fL / 2f = L
 *      vol = 3600 · v / 2L = 1800 v/L
 */

/* Main function */
int main() {
    int l, f;
    while (scanf("%d %d", &l, &f) == 2 && l > 0) {
        double v, vol;
        v = sqrt(2 * l * f);
        vol = 1800 * v / l;
        printf("%.8f %.8f\n", v, vol);
    }
    return EXIT_SUCCESS;
}
