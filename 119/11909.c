/* 11909
 * Soya Milk
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define PI  3.14159265358979323846

/* Main function */
int main() {
    int b, w, h, a;
    while (scanf("%d %d %d %d", &b, &w, &h, &a) != EOF) {
        double area, tang = tan(PI * a / 180);
        double p = tang * b;
        if (p < h)
            area = b * w * (h - p / 2);
        else {
            p = h / tang;
            area = h * p * w / 2;
        }
        printf("%.3f mL\n", area);
    }
    return EXIT_SUCCESS;
}
