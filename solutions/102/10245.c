/* 10245
 * The Closest Pair Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define SQ(x)       ((x) * (x))
#define INFINITY    10000
#define SQ_INFINITY SQ(INFINITY)
#define EPSILON     1e-5

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        struct {
            double x, y;
        } point[MAX_N];
        double minimum;
        int i, j;
        for (i = 0, minimum = SQ(INFINITY); i < n; i++) {
            assert(scanf("%lf %lf", &point[i].x, &point[i].y) != EOF);
            for (j = 0; j < i; j++) {
                double dist = SQ(point[i].x - point[j].x) + 
                        SQ(point[i].y - point[j].y);
                if (dist < minimum)
                    minimum = dist;
            }
        }
        if (minimum - SQ_INFINITY > -EPSILON)
            printf("INFINITY\n");
        else
            printf("%.4f\n", sqrt(minimum));
    }
    return EXIT_SUCCESS;
}
