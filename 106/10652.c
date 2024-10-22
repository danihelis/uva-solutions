/* 10652
 * Board Wrapping
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#if !defined(M_PI)
    #define M_PI        3.14159265358979
#endif
#define EPSILON         1e-5

#define ABS_DIFF(x, y)  ((x) > (y) ? (x) - (y) : (y) - (x))
#define EQUAL(x, y)     (ABS_DIFF(x, y) < EPSILON)
#define RAD(x)          ((x) * M_PI / 180)
#define SQ(x)           ((x) * (x))

#define DISTANCE(p, q)  (sqrt(SQ((p)->x - (q)->x) + SQ((p)->y - (q)->y)))

#define MAX_BOARDS  600
#define MAX_POINTS  (MAX_BOARDS * 4)

typedef struct {
    double x, y, angle, distance;
} point_t;

point_t point[MAX_POINTS], *p_point[MAX_POINTS];
point_t center, *hull[MAX_BOARDS];
int num_points, hull_size;
double board_area, hull_area;
    

/* Read points and compute board area */
void read_points() {
    int i, k, num_boards;
    center.x = 0, center.y = 0;
    board_area = 0;
    num_points = 0;
    assert(scanf("%d", &num_boards) != EOF);
    for (i = 0; i < num_boards; i++) {
        point_t board;
        double width, height, angle, base_angle, diagonal;
        assert(scanf("%lf %lf %lf %lf %lf", &board.x, &board.y, &width, 
                    &height, &board.angle) != EOF);
        board_area += width * height;
        center.x += board.x, center.y += board.y;
        diagonal = sqrt(SQ(width) + SQ(height)) / 2;
        base_angle = atan2(height, width);
        angle = base_angle - RAD(board.angle);
        height /= 2, width /= 2;
        for (k = 0; k < 4; k++) {
            point_t *p = &point[num_points];
            p->x = board.x + cos(angle) * diagonal;
            p->y = board.y + sin(angle) * diagonal;
            p_point[num_points++] = p;
            angle += k % 2 == 0 ? M_PI - 2 * base_angle : 2 * base_angle;
        }
    }
    center.x /= num_boards, center.y /= num_boards;
    for (i = 0; i < num_points; i++) {
        point_t *p = p_point[i];
        p->angle = atan2(p->y - center.y, p->x - center.x);
        p->distance = DISTANCE(p, &center);
    }
}

/* Compare two points by angle relative to center */
int compare(const void *a, const void *b) {
    point_t *x = * (point_t **) a, *y = * (point_t **) b;
    if (EQUAL(x->angle, y->angle))
        return x->distance < y->distance ? -1 : 1;
    return y->angle < x->angle ? -1 : 1;
}

/* Compute sine from three points acting as two segments from same origin */
double sine(point_t *p0, point_t *p1, point_t *p2) {
    double xd[2], yd[2];
    int k;
    for (k = 0; k < 2; k++) {
        xd[k] = (k ? p2 : p1)->x - p0->x;
        yd[k] = (k ? p2 : p1)->y - p0->y;
    }
    return xd[0] * yd[1] - xd[1] * yd[0];
}

/* Compute convex hull, along with its area */
#define NEXT(x)     ((x + 1) % num_points)
void compute_convex_hull() {
    int i, start;
    qsort(p_point, num_points, sizeof (point_t *), compare);
    for (i = 1, start = 0; i < num_points; i++)
        if (p_point[i]->x < p_point[start]->x)
            start = i;
    hull[0] = p_point[start], hull_size = 1;
    for (i = NEXT(start); i != start; i = NEXT(i)) {
        hull[hull_size++] = p_point[i];
        while (hull_size > 2 && sine(hull[hull_size - 3], 
                    hull[hull_size - 2], hull[hull_size - 1]) > -EPSILON) {
            hull[hull_size - 2] = hull[hull_size - 1];
            hull_size--;
        }
    }
    while (hull_size > 2 && sine(hull[hull_size - 2], 
                    hull[hull_size - 1], hull[0]) > -EPSILON)
        hull_size--;

    for (i = 2, hull_area = 0; i < hull_size; i++) {
        hull_area -= sine(hull[0], hull[i - 1], hull[i]) / 2;
    }
}

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        read_points();
        compute_convex_hull();
        printf("%.1f %%\n", board_area * 100 / hull_area);
    }
    return EXIT_SUCCESS;
}
