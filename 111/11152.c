/* 11152
 * Colourful Flowers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define PI 3.141592653589793238

/* Main function */
int main() {
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) != EOF) {
        double p = a + b + c;
        double s = p / 2;
        double area = sqrt(s * (s - a) * (s - b) * (s - c));
        double rad_int = area / s;
        double area_int = rad_int * rad_int * PI;
        double med = (b * b + c * c - a * a) * a / (4 * area);
        double area_ext = (a * a + med * med) * PI / 4;
        printf("%.4f %.4f %.4f\n", area_ext - area, area - area_int, area_int);
    }
    return 0;
}
