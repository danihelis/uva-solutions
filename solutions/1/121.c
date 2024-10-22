/**
 * 121
 * Pipe Fitters
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Calculate how many pipes fit in a skew model */
int maximum_skew(double x, double y) {
    double distance, height, overfit;
    int rows, skew, odd_skew;

    /* 1. Trying to use even rows */
    overfit = x - floor(x);
    distance = (overfit >= 0.5 ? 0.5 : 0); /* MIN(overfit, 0.5); */
    height = sqrt(1.0 - distance * distance);
    rows = (y + height - 1.0) / height;
    skew = floor(x) * rows;
    if (DEBUG) {
        printf("[EVEN] X=%.2f Y=%.2f Over=%.2f D=%.2f H=%.2f R=%d TOTAL=%d\n",
                x, y, overfit, distance, height, rows, skew);
    }

    /* 2. Trying to use odd rows */
    distance = 0.5;
    height = sqrt(1 - distance * distance);
    rows = (y + height - 1) / height;
    odd_skew = floor(x) * rows - rows / 2;
    if (DEBUG) {
        printf("[ODD]  X=%.2f Y=%.2f Over=%.2f D=%.2f H=%.2f R=%d TOTAL=%d\n",
                x, y, overfit, distance, height, rows, odd_skew);
    }
    return MAX(skew, odd_skew);
}

/* Main */
int main() {
    double x, y;
    int grid, skew_hor, skew_vert, skew;

    while (scanf("%lf %lf", &x, &y) == 2) {
        grid = ((int) x) * ((int) y);
        skew_hor = maximum_skew(x, y);
        skew_vert = maximum_skew(y, x);
        skew = MAX(skew_hor, skew_vert);
        if (grid >= skew) {
            printf("%d grid\n", grid);
        }
        else {
            printf("%d skew\n", skew);
        }
    }
    return 0;
}
