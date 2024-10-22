/**
 * 109
 * SCUB Busters
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_KINGDOMS 21
#define MAX_CITIES 101

typedef struct {
    int x, y;
} point_t, vector_t;

typedef struct {
    int size;
    point_t point[MAX_CITIES];
} polygon_t;

typedef struct {
    polygon_t cities;
    polygon_t hull;
    int bombed;
} kingdom_t;

kingdom_t kingdom[MAX_KINGDOMS];
int number_kingdoms;


#define SET_POINT(p, vx, vy) (p).x = (vx); (p).y = (vy)
#define COPY_POINT(p1, p2) SET_POINT(p1, (p2).x, (p2).y)
#define TO_VECTOR(v, a, b) (v).x = (b).x - (a).x; (v).y = (b).y - (a).y
#define DISTANCE(a, b) sqrt(((a).x - (b).x) * ((a).x - (b).x) + ((a).y - (b).y) * ((a).y - (b).y))


/* Calculate the cross product of two vectors. 
 * Remember that: a x b = |a| |b| sin t
 * Then it follows that: 1. a x b > 0 => sin t > 0 => 180° < t < 0°
 *                       2. a x b < 0 => sin t < 0 => 360° < t < 180°
 *                       3. a x b == 0 => t = 0° or t = 180° (a and b are collinear)
 */
int cross_product(vector_t a, vector_t b) {
    return (a.x * b.y) - (a.y * b.x);
}


/* Sort points by degree, in reference to a fixed point */
point_t anchor;
int compare_point(const void *a, const void *b) {
    vector_t va, vb;
    int prod;
    TO_VECTOR(va, anchor, *((point_t *) a));
    TO_VECTOR(vb, anchor, *((point_t *) b));
    prod = cross_product(va, vb);
    if (prod == 0) {
        /* Collinear points are ordered by distance */
        double da = DISTANCE(anchor, *((point_t *) a));
        double db = DISTANCE(anchor, *((point_t *) b));
        return da - db;
    }
    return prod;
}


/* Create a minimum convex hull around the given points */
int minimum_convex_hull(polygon_t *hull, polygon_t *poly) {
    int i;
    int hull_size = 0;

    /* We do not have a polygon with less than three points */
    if (poly->size < 3) {
        hull->size = 0;
        return 0;
    }

    /* Find the leftmost point to be the anchor */
    COPY_POINT(anchor, poly->point[0]);
    for (i = 1; i < poly->size; i++) {
        if (poly->point[i].x < anchor.x || (poly->point[i].x == anchor.x && poly->point[i].y < anchor.y)) {
            COPY_POINT(poly->point[0], poly->point[i]);
            COPY_POINT(poly->point[i], anchor);
            COPY_POINT(anchor, poly->point[0]);
        }
    }

    /* Sort all points in reference to the anchor */
    qsort(poly->point + 1, poly->size - 1, sizeof(point_t), compare_point);

    /* Determine the minimum convex hull, adding one point after another and
     * checking if the angle is lesser then 180°
     */
    COPY_POINT(hull->point[0], anchor);
    COPY_POINT(hull->point[1], poly->point[1]);
    hull_size = 2;
    for (i = 2; i < poly->size; i++) {
        COPY_POINT(hull->point[hull_size], poly->point[i]);
        hull_size++;
        while (hull_size > 2) {
            vector_t a, b;
            TO_VECTOR(a, hull->point[hull_size - 2], hull->point[hull_size - 3]);
            TO_VECTOR(b, hull->point[hull_size - 2], hull->point[hull_size - 1]);
            if (cross_product(a, b) > 0) {
                break;
            }
            else {
                COPY_POINT(hull->point[hull_size - 2], hull->point[hull_size - 1]);
                hull_size--;
            }
        }
    }

    /* Check last hull point against the anchor */
    while (hull_size > 3) {
        vector_t a, b;
        TO_VECTOR(a, hull->point[hull_size - 1], hull->point[hull_size - 2]);
        TO_VECTOR(b, hull->point[hull_size - 1], anchor);
        if (cross_product(a, b) > 0) {
            break;
        }
        else {
            COPY_POINT(hull->point[hull_size - 1], anchor);
            hull_size--;
        }
    }
    hull->size = hull_size;
    return hull_size;
}


/* Verify if a point in inside the convex polygon.
 * To check if the point is inside, we calculate the angle it forms
 * with every two polygon points. The angle must be lesser than or equal 180°.
 */
int is_inside(point_t p, polygon_t *poly) {
    int i;
    for (i = 0; i < poly->size; i++) {
        vector_t a, b;
        TO_VECTOR(a, p, poly->point[i]);
        TO_VECTOR(b, p, poly->point[(i + 1) % poly->size]);
        if (cross_product(b, a) < 0) {
            return 0;
        }
    }
    return 1;
}


/* Calculate the area of a convex polygon */
int double_area(polygon_t *poly) {
    int i;
    int sum = 0;
    for (i = 0; i < poly->size; i++) {
        int j = (i + 1) % poly->size;
        sum += poly->point[i].x * poly->point[j].y - poly->point[j].x * poly->point[i].y;
    }
    return - sum; /* the minus signal is used because we travel the polygon clockwise */
}


/* Main */
int main() {
    int size, x, y, i;
    int total_area = 0;
    int halves = 0;
    
    /* Read kingdom cities and calculate territory as a convex hull */
    number_kingdoms = 0;
    while (scanf("%d", &size) == 1) {
        if (size == -1) {
            break;
        }
        kingdom[number_kingdoms].cities.size = size;
        kingdom[number_kingdoms].bombed = 0;

        for (i = 0; i < size; i++) {
            scanf("%d %d", &x, &y);
            SET_POINT(kingdom[number_kingdoms].cities.point[i], x, y);
        }
        minimum_convex_hull(&kingdom[number_kingdoms].hull, &kingdom[number_kingdoms].cities);

        /*
        printf("Kingdom %d -- Polygon hull (size = %d)\n", number_kingdoms + 1,
                kingdom[number_kingdoms].hull.size);
        for (i = 0; i < kingdom[number_kingdoms].hull.size; i++) {
            printf("City %d: (%d, %d)\n", i, kingdom[number_kingdoms].hull.point[i].x, 
                    kingdom[number_kingdoms].hull.point[i].y);
        }
        */
        
        number_kingdoms++;
    }
    
    /* Bombard all map (and some kingdoms) */ 
    while (scanf("%d %d", &x, &y) == 2) {
        point_t bomb;
        SET_POINT(bomb, x, y);
        for (i = 0; i < number_kingdoms; i++) {
            if (!kingdom[i].bombed && is_inside(bomb, &kingdom[i].hull)) {
                kingdom[i].bombed = 1;
            }
        }
    }

    /* Sum up all damaged kingdom areas */
    for (i = 0; i < number_kingdoms; i++) {
        if (kingdom[i].bombed) {
            int kingdom_area = double_area(&kingdom[i].hull);
            halves += kingdom_area % 2;
            total_area += (kingdom_area >> 1);
        }
    }

    printf("%.2f\n", total_area + 0.5 * halves);

    return 0;
}
