/* 10310
 * Dog and Gopher
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SQ(x)       ((x) * (x))
#define DIST(a,b)   (SQ((a).x - (b).x) + SQ((a).y - (b).y))
#define READ(p)     (scanf("%lf %lf", &(p).x, &(p).y) == 2)
#define EPSILON     0.001

typedef struct {
    double x, y;
} point_t;

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int escape;
        point_t g, d, p, s = {0, 0};
        assert(READ(g) && READ(d));
        for (escape = 0; n > 0; n--) {
            assert(READ(p));
            if (!escape) {
                double dg = DIST(g, p), dd = DIST(d, p);
                if (dg * 4 < dd + EPSILON)
                    escape = 1, s = p;
            }
        }
        if (escape)
            printf("The gopher can escape through the hole at "
                   "(%.3f,%.3f).\n", s.x, s.y);
        else
            printf("The gopher cannot escape.\n");
    }
    return EXIT_SUCCESS;
}
