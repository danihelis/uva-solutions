/* 11437
 * Triangle Fun
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROUND(x)        (floor((x) + 0.5))

typedef struct {
    double x, y;
} point_t;

typedef struct {
    point_t origin, direction;
} line_t;


/* Computes the difference between two points */
point_t difference(point_t a, point_t b) {
    point_t d;
    d.x = a.x - b.x;
    d.y = a.y - b.y;
    return d;
}


/* Return a new point between p1 and p2 that divides the segment into 1:2 */
point_t get_divider(point_t p1, point_t p2) {
    point_t d;
    point_t diff = difference(p2, p1);
    d.x = p1.x + diff.x / 3;
    d.y = p1.y + diff.y / 3;
    return d;
}


/* Computes the determinant of 2 points */
double det2d(point_t a, point_t b) {
    return a.x * b.y - a.y * b.x;
}


/* Computes the determinant of 3 points */
double det3d(point_t a, point_t b, point_t c) {
    return det2d(difference(a, b), difference(a, c));
}


/* Return the point in the intersection between two lines */
point_t get_intersection(line_t l1, line_t l2) {
    double alpha = det2d(difference(l2.origin, l1.origin), l2.direction) /
        det2d(l1.direction, l2.direction);
    point_t i;
    i.x = l1.origin.x + l1.direction.x * alpha;
    i.y = l1.origin.y + l1.direction.y * alpha;
    return i;
}


/* Compute the inner triangle points and the area inside it */
double get_inner_triangle_area(point_t a, point_t b, point_t c) {
    point_t d, e, f, p, q, r;
    line_t la, lb, lc;

    d = get_divider(b, c);
    e = get_divider(c, a);
    f = get_divider(a, b);

    la.origin = a;
    la.direction = difference(d, a);

    lb.origin = b;
    lb.direction = difference(e, b);

    lc.origin = c;
    lc.direction = difference(f, c);

    p = get_intersection(la, lb);
    q = get_intersection(lb, lc);
    r = get_intersection(lc, la);

    return fabs(det3d(p, q, r)) / 2;
}


/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        point_t p[3];
        int i;

        for (i = 0; i < 3; i++) {
            assert(scanf("%lf %lf", &p[i].x, &p[i].y) == 2);
        }
        printf("%.0f\n", ROUND(get_inner_triangle_area(p[0], p[1], p[2])));
    }

    return EXIT_SUCCESS;
}
