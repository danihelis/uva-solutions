/* 10577
 * Bounding box
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define EPSILON     1e-7
#define PI          3.141592653589793238462632385

#define GEZ(x)      ((x) > -EPSILON)
#define LEZ(x)      ((x) < EPSILON)
#define ZERO(x)     (GEZ(x) && LEZ(x))
#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

typedef struct {
    double x, y;
} point_t;

typedef struct {
    double rad;
    point_t center;
} circle_t;


/* Scale a vector */
point_t scale(point_t p, double v) {
    p.x *= v, p.y *= v;
    return p;
}

/* Get the norm of a vector */
double norm(point_t p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

/* Normalize vector */
point_t normalize(point_t p) {
    double v = norm(p);
    p.x /= v, p.y /= v;
    return p;
}

/* Sum of vectors */
point_t sum(point_t a, point_t b) {
    a.x += b.x, a.y += b.y;
    return a;
}

/* Difference between vectors */
point_t diff(point_t a, point_t b) {
    a.x -= b.x, a.y -= b.y;
    return a;
}

/* Orthogonal vector */
point_t ortho(point_t a) {
    point_t b = {0, 1};
    if (!ZERO(a.y))
        b.x = -1, b.y = a.x / a.y;
    return normalize(b);
}

/* Cossine between vectors */
double cossine(point_t a, point_t b) {
    double n = norm(a) * norm(b);
    return (a.x * b.x + a.y * b.y) / n;
}

/* Intersection between two circles of same radius */
void circle_inter(point_t a, point_t b, double rad, point_t *p1, 
        point_t *p2) {
    point_t m, h, d = diff(a, b);
    double delta, eta;
    delta = norm(d) / 2;
    eta = rad * rad - delta * delta;
    assert(GEZ(eta));
    m = sum(b, scale(d, 0.5));
    h = scale(ortho(d), sqrt(eta));
    *p1 = sum(m, h);
    *p2 = diff(m, h);
}

/* Get circle that circumscribe triangle */
circle_t get_circle(point_t a, point_t b, point_t c) {
    point_t o1, o2, sa = diff(a, c), sb = diff(b, c);
    double cos_angle = cossine(sa, sb), side = norm(diff(sa, sb));
    circle_t k;
    k.rad = sqrt(side * side / (4 - 4 * cos_angle * cos_angle));
    circle_inter(a, b, k.rad, &o1, &o2);
    k.center = fabs(k.rad - norm(diff(o1, c))) < 
            fabs(k.rad - norm(diff(o2, c))) ? o1 : o2;
    return k;
}

/* Find squared area of regular polygon inscribed in a circle */
double area(circle_t k, point_t p, int n) {
    point_t max = p, min = p, ndir, dir = diff(p, k.center);
    int i;
    for (i = 1; i < n; i++) {
        double cosr = cos(2 * PI * i / n), sinr = sin(2 * PI * i / n);
        ndir.x = dir.x * cosr - dir.y * sinr;
        ndir.y = dir.x * sinr + dir.y * cosr;
        p = sum(k.center, ndir);
        max.x = MAX(max.x, p.x), max.y = MAX(max.y, p.y);
        min.x = MIN(min.x, p.x), min.y = MIN(min.y, p.y);
    }
    return (max.x - min.x - EPSILON) * (max.y - min.y - EPSILON);
}

/* Main function */
int main() {
    int i, n, test = 0;
    while (scanf("%d", &n) != EOF && n > 0) {
        point_t p[3];
        circle_t k;
        for (i = 0; i < 3; i++)
            assert(scanf("%lf %lf", &p[i].x, &p[i].y) != EOF);
        k = get_circle(p[0], p[1], p[2]);
        printf("Polygon %d: %.3f\n", ++test, area(k, p[0], n));
    }
    return EXIT_SUCCESS;
}
