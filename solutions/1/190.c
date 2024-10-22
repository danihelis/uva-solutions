/* 190
 * Circle Through Three Points
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    double x, y;
} point_t;

#define READ(p)         (scanf("%lf %lf", &(p).x, &(p).y) != EOF)
#define MIDDLE(r, a, b) (r).x = ((a).x + (b).x) / 2; (r).y = ((a).y + (b).y) / 2
#define DIFF(r, a, b)   (r).x = (a).x - (b).x; (r).y = (a).y - (b).y
#define ORTHO(r, v)     (r).x = ((v).y == 0 ? 0 : 1); (r).y = ((v).y == 0 ? 1 : - (v).x / (v).y)
#define DET(a, b)       ((a).x * (b).y - (a).y * (b).x)
#define SQ(v)           ((v) * (v))
#define PRINT(b, v, a)  printf("%s %c %.3f%s", b, (v) < 0 ? '-' : '+', fabs(v), a)

/* Main function */
int main() {
    point_t a, b, c;
    while (READ(a) && READ(b) && READ(c)) {
        point_t o, m_a, d_a, r_a, m_b, d_b, r_b, delta;
        double alpha, dist;
        MIDDLE(m_a, a, c); MIDDLE(m_b, b, c);
        DIFF(d_a, a, c); DIFF(d_b, b, c);
        ORTHO(r_a, d_a); ORTHO(r_b, d_b);
        DIFF(delta, m_b, m_a);
        alpha = DET(delta, r_b) / DET(r_a, r_b);
        o.x = m_a.x + alpha * r_a.x, o.y = m_a.y + alpha * r_a.y;
        DIFF(delta, o, a);
        dist = SQ(delta.x) + SQ(delta.y);
        o.x *= -1, o.y *= -1;

        PRINT("(x", o.x, ")^2");
        PRINT(" + (y", o.y, ")^2");
        printf(" = %.3f^2\nx^2 + y^2", sqrt(dist));
        alpha = 2 * o.x; 
        PRINT("", alpha, "x");
        alpha = 2 * o.y; 
        PRINT("", alpha, "y");
        alpha = SQ(o.x) + SQ(o.y) - dist; 
        PRINT("", alpha, "");
        printf(" = 0\n\n");
    }
    return 0;
}
