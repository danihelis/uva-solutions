/* 10432
 * Polygon Inside A Circle
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define PI  3.14159265358979

/* Main function */
int main() {
    double n, r;
    while (scanf("%lf %lf", &r, &n) != EOF) {
        double angle = (n - 2) * PI / n;
        double area = r * r * n * sin(angle) / 2;
        printf("%.3f\n", area);
    }
    return 0;
}
