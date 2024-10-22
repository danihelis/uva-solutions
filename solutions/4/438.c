/* 438
 * The Circumference of the Circle
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define PI              3.141592653589793
#define SCAN(p)         (scanf("%lf %lf", &p.x, &p.y) != EOF)
#define SQ(x)           ((x) * (x))
#define COEF(p1, p2, f) (2 * p1.f - 2 * p2.f)
#define RHS(p1, p2)     (SQ(p1.x) + SQ(p1.y) - SQ(p2.x) - SQ(p2.y))


typedef struct {
    double x, y;
} point_t;

/* Main function */
int main() {
    point_t a, b, c, p;
    while (SCAN(a) && SCAN(b) && SCAN(c)) {
        point_t e1, e2;
        double d1, d2, det, radius, circ;
        e1.x = COEF(b, a, x), e1.y = COEF(b, a, y);
        e2.x = COEF(c, a, x), e2.y = COEF(c, a, y);
        d1 = RHS(b, a), d2 = RHS(c, a);
        det = e1.x * e2.y - e1.y * e2.x;
        p.x = (d1 * e2.y - e1.y * d2) / det;
        p.y = (e1.x * d2 - d1 * e2.x) / det;
        radius = sqrt(SQ(p.x - a.x) + SQ(p.y - a.y));
        circ = 2 * radius * PI;
        printf("%.2f\n", circ);
    }
    return 0;
}
