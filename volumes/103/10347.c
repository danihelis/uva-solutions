/* 10347
 * Medians
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
    double v[3];
    while (scanf("%lf %lf %lf", &v[0], &v[1], &v[2]) == 3) {
        int i, feasible;
        double s, p;
        for (i = 0, s = 0; i < 3; i++)
            s += v[i];
        for (i = 0, p = s /= 2, feasible = 1; feasible && i < 3; i++)
            if (s <= v[i])
                feasible = 0;
            else
                p *= (s - v[i]);
        if (!feasible || p < 1e-4)
            printf("-1.000\n");
        else {
            p = sqrt(p) * 4 / 3;
            printf("%.3f\n", p);
        }
    }
    return EXIT_SUCCESS;
}
