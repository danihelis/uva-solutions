/* 10297
 * Beavergnaw
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
    int diam, volume;
    double pi = 2 * acos(0);
    while (scanf("%d %d", &diam, &volume) != EOF && diam > 0) {
        double d = pow(diam, 3.0) - 6.0 * volume / pi;
        d = pow(d, 1.0 / 3.0);
        printf("%.3f\n", d);
    }
    return EXIT_SUCCESS;
}
