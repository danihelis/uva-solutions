/* 11265
 * The Sultan's Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SEGMENTS  500
#define MAX_POINTS    (MAX_SEGMENTS * MAX_SEGMENTS)

#define EPSILON     1e-7
#define ZERO(x)     ((x) > 0 ? (x) < EPSILON : (x) > -EPSILON)
#define GT(x,y)     ((x) > (y) + EPSILON)
#define GEQ(x,y)    ((x) > (y) - EPSILON)

typedef struct {
    double x, y;
} point_t, vector_t;

point_t hull[MAX_POINTS], center;
int hull_size;

/* Vector difference */
vector_t v_diff(point_t p1, point_t p2) {
    vector_t v;
    v.x = p1.x - p2.x, v.y = p1.y - p2.y;
    return v;
}

/* Vector cross product */
double v_cross_product(vector_t a, vector_t b) {
    return a.x * b.y - a.y * b.x;
}

/* Compute (square) distance between two points */
double distance(point_t a, point_t b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

/* Compute angle between BA and CA, where A is the anchor */
double angle(point_t a, point_t b, point_t c) {
    return v_cross_product(v_diff(c, a), v_diff(b, a));
}

/* Intersection between segments */
int intersection(point_t s1, point_t s2, point_t t1, point_t t2,
        point_t *q) {
    vector_t s = v_diff(s2, s1), t = v_diff(t2, t1);
    vector_t delta;
    double a, d = v_cross_product(s, t);
    if (ZERO(d))
        return 0;
    delta = v_diff(t1, s1);
    a = v_cross_product(delta, t) / d;
    if (!GT(a, 0) || GEQ(a, 1))
        return 0;
    q->x = s1.x + s.x * a, q->y = s1.y + s.y * a;
    return 1;
}

/* Compare points (for convex hull) */
point_t anchor;
int compare_points(const void *a, const void *b) {
    point_t *x = (point_t *) a, *y = (point_t *) b;
    double ang = angle(anchor, *y, *x);
    if (ZERO(ang))
        return distance(anchor, *x) < distance(anchor, *y) ? -1 : 1;
    return ang < 0 ? -1 : 1;
}

/* Sort hull */
void sort_hull() {
    int i;
    for (i = 1, anchor = hull[0]; i < hull_size; i++)
        if (hull[i].x < anchor.x || (ZERO(hull[i].x - anchor.x) &&
                hull[i].y < anchor.y))
            anchor = hull[i];
    qsort(hull, hull_size, sizeof (point_t), compare_points);
}

/* Add segment to polygon */
void add_segment(point_t s1, point_t s2) {
    point_t q[2], dummy;
    int i, j, num_inters;

    for (i = 0, num_inters = 0; i < hull_size && num_inters < 2; i++)
        if (intersection(hull[i], hull[(i + 1) % hull_size], s1, s2,
                    &q[num_inters]))
            num_inters++;
    i = 0;
    while (i < hull_size)
        if (!GEQ(angle(s1, s2, center) * angle(s1, s2, hull[i]), 0))
            for (j = i, --hull_size; j < hull_size; j++)
                hull[j] = hull[j + 1];
        else
            i++;
    for (i = 0; i < num_inters; i++)
        hull[hull_size++] = q[i];
    sort_hull();
}

/* Compute area of convex hull */
double compute_area() {
    int i;
    double area = 0;
    for (i = 2; i < hull_size; i++) {
        area += v_cross_product(v_diff(hull[i], hull[0]),
                v_diff(hull[i - 1], hull[0]));
    }
    return area / 2;
}

/* Main function */
int main() {
    int test = 0;
    int i, n, width, height;
    while (scanf("%d %d %d %lf %lf", &n, &width, &height, 
                &center.x, &center.y) != EOF) {
        for (i = 0; i < 4; i++) {
            hull[i].x = (i % 2 == 0 ? 0 : width);
            hull[i].y = (i / 2 == 0 ? 0 : height);
        }
        hull_size = 4;
        sort_hull();
        for (i = 0; i < n; i++) {
            point_t s1, s2;
            assert(scanf("%lf %lf %lf %lf", &s1.x, &s1.y, 
                        &s2.x, &s2.y) != EOF);
            add_segment(s1, s2);
        }
        printf("Case #%d: %.3f\n", ++test, compute_area());
    }

    return EXIT_SUCCESS;
}
