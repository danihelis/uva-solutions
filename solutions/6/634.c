/* 634
 * Polygon
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#define MIN(a,b)    ((a) < (b) ? (a) : (b))

typedef struct {
    int x, y;
} point_t;

point_t vertex[MAX_N], point;
int num_vertices;

/* Return number of intersections */
int get_intersections() {
    int i, count;
    for (i = count = 0; i <= num_vertices; i++) {
        point_t *p = &vertex[i], *q = &vertex[(i + 1) % num_vertices];
        if (p->x == q->x && p->x > point.x) {
            count += point.y > MIN(p->y, q->y) && 
                point.y < MAX(p->y, q->y) ? 1 : 0;
        }
    }
    return count;
}

/* Main function */
int main() {
    while (scanf("%d", &num_vertices) == 1 && num_vertices > 0) {
        int i;
        for (i = 0; i < num_vertices; i++) {
            point_t *p = &vertex[i];
            assert(scanf("%d %d", &p->x, &p->y) == 2);
        }
        assert(scanf("%d %d", &point.x, &point.y) == 2);
        printf("%c\n", get_intersections() % 2 == 0 ? 'F' : 'T');
    }
    return EXIT_SUCCESS;
}
