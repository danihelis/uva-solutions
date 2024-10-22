/* 11130
 * Billiard bounces
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#define PI  3.1415926535897932385

/* Main function */
int main() {
    int k, side[2], veloc, time, angle, count[2];
    while (scanf("%d %d %d %d %d", &side[0], &side[1], &veloc, &angle, &time) != EOF &&
            side[0] > 0) {
        double s, rad; 
        for (k = 0, rad = angle * PI / 180; k < 2; k++) {
            s = (side[k] + (k == 0 ? cos(rad) : sin(rad)) * veloc * time) / 2;
            count[k] = (int) (s / side[k]);
        }
        printf("%d %d\n", count[0], count[1]);
    }
    return 0;
}
