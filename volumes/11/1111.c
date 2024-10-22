/* 1111
 * Trash Removal
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_POINTS  100

#define EPSILON     1e-7
#define ZERO(x)     ((x) > 0 ? (x) < EPSILON : (x) > -EPSILON)

typedef struct {
    double x, y;
} point_t, vector_t;

point_t polygon[MAX_POINTS], hull[MAX_POINTS];
point_t anchor;
int num_points, hull_size;


/* Difference */
vector_t diff(vector_t a, vector_t b) {
    vector_t d;
    d.x = a.x - b.x, d.y = a.y - b.y;
    return d;
}

/* Norm */
double sq_norm(vector_t v) {
    return v.x * v.x + v.y * v.y;
}

/* Normalize */
void normalize(vector_t *v) {
    double n = sqrt(sq_norm(*v));
    v->x /= n, v->y /= n;
}

/* Orthogonal */
vector_t orthogonal(vector_t v) {
    vector_t ortho = {0, 1};
    if (!ZERO(v.y)) {
        ortho.x = 1, ortho.y = -1.0 * v.x / v.y;
        normalize(&ortho);
    }
    return ortho;
}

/* Cross product */
double cross_product(vector_t a, vector_t b) {
    return a.x * b.y - a.y * b.x;
}

/* Angle between three points */
double angle(point_t a, point_t b, point_t c) {
    return cross_product(diff(c, a), diff(b, a));
}

/* Is angle concave? */
int concave_angle(point_t a, point_t b, point_t c) {
    return angle(a, b, c) < 0;
}

/* Compare points to for convex hull */
int compare_point(const void *a, const void *b) {
    point_t *x = (point_t *) a, *y = (point_t *) b;
    double arg = angle(anchor, *y, *x);
    if (ZERO(arg))
        return sq_norm(diff(*x, anchor)) - sq_norm(diff(*y, anchor));
    return arg;
}

/* Create convex hull */
void create_convex_hull() {
    int i;

    /* Sort all points in reference to the center */
    for (i = 1, anchor = polygon[0]; i < num_points; i++)
        if (polygon[i].x < anchor.x ||
                (ZERO(polygon[i].x - anchor.x) && polygon[i].y < anchor.y))
            anchor = polygon[i];
    qsort(polygon, num_points, sizeof (point_t), compare_point);

    /* Build convex hull */
    hull[0] = polygon[0], hull_size = 1;
    for (i = 1; i < num_points; i++) {
        hull[hull_size++] = polygon[i];
        while (hull_size > 2 && concave_angle(hull[hull_size - 3],
                hull[hull_size - 2], hull[hull_size - 1])) {
            hull[hull_size - 2] = hull[hull_size - 1];
            hull_size--;
        }
    }
    while (hull_size > 3 && concave_angle(hull[hull_size - 2], 
                hull[hull_size - 1], hull[0]))
        hull_size--;
}

/* Distance */
double distance(point_t vertex, vector_t edge, vector_t ortho, point_t p) {
    point_t inter;
    double scalar;
    scalar = cross_product(diff(p, vertex), edge) / 
            cross_product(ortho, edge);
    inter.x = vertex.x + ortho.x * scalar;
    inter.y = vertex.y + ortho.y * scalar;
    return sqrt(sq_norm(diff(inter, vertex)));
}

/* Find minimum gap */
double find_minimum_gap() {
    vector_t edge, ortho;
    double mininum, gap;
    int i, k;
    for (i = 0, mininum = -1; i < hull_size; i++) {
        point_t vertex = hull[i];
        point_t second = hull[(i + hull_size - 1) % hull_size];
        edge = diff(vertex, second);
        normalize(&edge);
        ortho = orthogonal(edge);
        for (k = 0, gap = 0; k < hull_size; k++) {
            double d = distance(vertex, edge, ortho, hull[k]);
            if (d > gap)
                gap = d;
        }
        if (mininum < 0 || gap < mininum)
            mininum = gap;
    }
    return mininum;
}

/* Main function */
int main() {
    int i, test = 0;
    while (scanf("%d", &num_points) != EOF && num_points > 0) {
        for (i = 0; i < num_points; i++) {
            point_t *p = &polygon[i];
            assert(scanf("%lf %lf", &p->x, &p->y) != EOF);
        }
        create_convex_hull();
        printf("Case %d: %.2f\n", ++test, find_minimum_gap());
    }
    return EXIT_SUCCESS;
}
