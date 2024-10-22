/* 10221
 * Satellites
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define RADIUS      6440
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    double pi = 4 * atan(1);
    double conversion = pi / 180;
    int dist, units;
    char type;
    while (scanf("%d %d %c%*s", &dist, &units, &type) == 3) {
        double angle = units * conversion;
        double arc, chord;
        if (type == 'm')
            angle /= 60;
        dist += RADIUS;
        arc = MIN(angle * dist, (2 * pi - angle) * dist); 
        chord = sqrt(2 * dist * dist * (1 - cos(angle)));
        printf("%.6f %.6f\n", arc, chord);
    }
    return EXIT_SUCCESS;
}
