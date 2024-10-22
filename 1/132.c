/**
 * 132
 * Bumpy Objects
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME   25
#define MAX_POINTS 1000

typedef struct {
    int x, y;
} point_t, vector_t;

typedef struct {
    point_t p;
    int index;
} poly_point_t;

typedef struct {
    double x, y;
} d_point_t, d_vector_t;

typedef struct {
    d_point_t p;
    d_vector_t v;
} line_t;

point_t mass_center;
poly_point_t polygon[MAX_POINTS];
point_t hull[MAX_POINTS];
int size_poly, size_hull;

/* Some useful macros */
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define COPY_POINT(p1, p2) (p1).x = (p2).x; (p1).y = (p2).y
#define TO_VECTOR(v, p1, p2) (v).x = (p1).x - (p2).x; (v).y = (p1).y - (p2).y
#define TO_LINE(s, p1, p2) COPY_POINT((s).p, p1); TO_VECTOR((s).v, p1, p2)
#define TO_RIGHT_ANGLE_VECTOR(v1, v2) (v1).x = ((v2).y == 0 ? 0 : 1); (v1).y = ((v2).y == 0 ? 1 : - (v2).x / (v2).y)
#define DISTANCE(p1, p2) sqrt(((p1).x - (p2).x) * ((p1).x - (p2).x) + ((p1).y - (p2).y) * ((p1).y - (p2).y))
#define DETERMINANT(v1, v2) ((v1).x * (v2).y - (v1).y * (v2).x)
#define CROSS_PRODUCT(v1, v2) DETERMINANT(v1, v2)

/* Compare polygon points by angular inclination from anchor */
poly_point_t anchor;
int compare_angle(const void *a, const void *b) {
    poly_point_t *x = ((poly_point_t *) a), *y = ((poly_point_t *) b);
    vector_t v1, v2;
    int prod;
    TO_VECTOR(v1, anchor.p, x->p);
    TO_VECTOR(v2, anchor.p, y->p);
    prod = CROSS_PRODUCT(v1, v2);
    if (prod != 0) {
        return prod;
    }
    else {
        return DISTANCE(anchor.p, x->p) - DISTANCE(anchor.p, y->p);
    }
}


/* Create convex hull & polygon edges*/
void create_convex_hull() {
    int p;

    anchor = polygon[0];
    for (p = 1; p < size_poly; p++) {
        if (polygon[p].p.x < anchor.p.x || (polygon[p].p.x == anchor.p.x && polygon[p].p.y < anchor.p.y)) {
            polygon[0] = anchor;
            anchor = polygon[p];
            polygon[p] = polygon[0];
        }
    }
    qsort(polygon + 1, size_poly - 1, sizeof (poly_point_t), compare_angle);
    polygon[0] = anchor;
    
    hull[0] = anchor.p;
    size_hull = 1;
    for (p = 1; p <= size_poly; p++) {
        hull[size_hull++] = polygon[p % size_poly].p;
        while (size_hull > 2) {
            vector_t v1, v2;
            int prod;
            TO_VECTOR(v1, hull[size_hull - 2], hull[size_hull - 3]);
            TO_VECTOR(v2, hull[size_hull - 2], hull[size_hull - 1]);
            prod = CROSS_PRODUCT(v1, v2);
            if (prod <= 0) {
                hull[size_hull - 2] = hull[size_hull - 1];
                size_hull--;
            }
            else {
                break;
            }
        }
    }
}


/* Find point of intersection between two lines */
void intersection(d_point_t *p_int, line_t *a, line_t *b) {
    double beta;
    vector_t dif_point;
    TO_VECTOR(dif_point, b->p, a->p);
    beta = -1.0 * DETERMINANT(a->v, dif_point) / DETERMINANT(a->v, b->v);
    p_int->x = b->p.x + beta * b->v.x;
    p_int->y = b->p.y + beta * b->v.y;
}


/* Find lowest edge that support polygon */
int find_lowest_edge() {
    line_t right_line;
    int e, best_index = size_poly;

    create_convex_hull();
    right_line.p.x = mass_center.x;
    right_line.p.y = mass_center.y;
    for (e = 1; e < size_hull; e++) {
        line_t line;
        d_point_t inters;
        double edge_distance = DISTANCE(hull[e - 1], hull[e]);

        TO_LINE(line, hull[e - 1], hull[e]);
        TO_RIGHT_ANGLE_VECTOR(right_line.v, line.v);
        intersection(&inters, &line, &right_line);

        if (DISTANCE(inters, hull[e - 1]) <= edge_distance && DISTANCE(inters, hull[e]) <= edge_distance) {
            /* Check for colinear points in the edge */
            int p, index = -1;

            for (p = 0; p < size_poly; p++) {
                vector_t v1, v2;
                TO_VECTOR(v1, polygon[p].p, hull[e - 1]);
                TO_VECTOR(v2, polygon[p].p, hull[e]);
                if (CROSS_PRODUCT(v1, v2) == 0) {
                    index = MAX(index, polygon[p].index);
                }
            }
            if (index < best_index) {
                best_index = index;
            }
        }
    }
    return best_index;
}


/* Main */
int main() {
    char object[MAX_NAME];

    while (scanf("%s", object) == 1) {
        if (strcmp(object, "#") == 0) {
            break;
        }
        scanf("%d %d", &mass_center.x, &mass_center.y);
        size_poly = 0;
        while (scanf("%d %d", &polygon[size_poly].p.x, &polygon[size_poly].p.y) == 2) {
            if (polygon[size_poly].p.x == 0 && polygon[size_poly].p.y == 0) {
                break;
            }
            polygon[size_poly].index = size_poly + 1;
            size_poly++;
        }
        printf("%-20s%d\n", object, find_lowest_edge());
    }
    return 0;
}

