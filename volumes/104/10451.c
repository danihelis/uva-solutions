/* 10451
 * Ancient Village Sports
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define PI  3.141592653589793238

/* Main function */
int main() {
    int test = 0, n;
    double area;
    while (scanf("%d %lf", &n, &area) != EOF && n >= 3) {
        double angle = (n - 2) * PI / n;
        double r_sq = 2 * area / (n * sin(angle));
        double r = sqrt(r_sq) * sin(angle / 2);
        double outer = r_sq * PI - area;
        double inner = area - r * r * PI;
        printf("Case %d: %.5f %.5f\n", ++test, outer, inner);
    }
    return 0;
}
