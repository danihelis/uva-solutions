/* 10195
 * The Knights Of The Round Table
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    double a, b, c, d, h, r;
    while (scanf("%lf %lf %lf", &a, &b, &c) != EOF) {
        d = (c * c + b * b - a * a) / (2 * c);
        h = sqrt(b * b - d * d);
        r = c * h / (a + b + c);
        if (a == 0 || b == 0 || c == 0) {
            r = 0;
        }
        printf("The radius of the round table is: %.3f\n", r);
    }
    return 0;
}
