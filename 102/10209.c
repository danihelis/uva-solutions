/* 10209
 * Is This Integration ?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Areas computed through integration offline:
 *      interior = PI/3 + SQRT(3) + 1
 *      exterior = 4 - 2·PI/3 - SQRT(3)
 *      middle   = PI/3 + 2·SQRT(3) - 4
 */
double interior = 0.31514674362772044,
       exterior = 0.17355409003792754,
       middle   = 0.5112991663343518;

/* Main function */
int main() {
    double radius;
    while (scanf("%lf", &radius) != EOF) {
        radius *= radius;
        printf("%.3f %.3f %.3f\n", interior * radius,
                middle * radius, exterior * radius);
    }
    return EXIT_SUCCESS;
}
