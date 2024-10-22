/* 10341
 * Solve It
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ITERACTIONS 100
#define APPROX          1e-7

int p, q, r, s, t, u;

/* Function definition */
double function(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

/* Main function */
int main() {
    while (scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) != EOF) {
        double low = 0, flow = function(0), high = 1, fhigh = function(1), x, fx;
        if (flow * fhigh > 0) {
            printf("No solution\n");
        }
        else if (fabs(flow) < APPROX) {
            printf("0.0000\n");
        }
        else if (fabs(fhigh) < APPROX) {
            printf("1.0000\n");
        }
        else {            
            while (fabs(high - low) > APPROX) {
                x = (low + high) / 2;
                fx = function(x);
                if (fx * fhigh < 0) {
                    low = x;
                }
                else {
                    high = x;
                    fhigh = fx;
                }
            }
            x = (high + low) / 2;
            printf("%.4f\n", x);
        }
    }
    return 0;
}
