/* 12696
 * Cabin Baggage
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
    int accepted, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (accepted = 0; num_tests > 0; num_tests--) {
        const int dim[4] = {5600, 4500, 2500, 700}, max = 12500;
        int a, i, v, vi, vf, sum;
        for (i = sum = 0, a = 1; i < 4; i++) {
            assert(scanf("%d.%d", &vi, &vf) == 2);
            v = vi * 100 + vf;
            if (i < 3)
                a &= v <= dim[i], sum += v;
        }
        a = ((a || sum <= max) && v <= dim[3]) ? 1 : 0;
        printf("%d\n", a);
        accepted += a;
    }
    printf("%d\n", accepted);
    return EXIT_SUCCESS;
}
