/* 10078
 * The Art Gallery
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   50

typedef struct {
    int x, y;
} point_t, vector_t;

point_t polygon[MAX_N];
int n;

/* Difference between two points */
vector_t diff(point_t a, point_t b) {
    point_t d;
    d.x = a.x - b.x, d.y = a.y - b.y;
    return d;
}

/* Cross product between two vectors */
int product(vector_t a, vector_t b) {
    return a.x * b.y - a.y * b.x;
}

/* Orientation */
int orientation(point_t p0, point_t p1, point_t p2) {
    return product(diff(p2, p0), diff(p1, p2)) > 0 ? 1 : -1;
}

/* whether the polygon is convex */
int is_convex() {
    int i, dir;
    dir = orientation(polygon[0], polygon[1], polygon[2]);
    for (i = 3; i <= n + 1; i++) 
        if (dir != orientation(polygon[i - 2], polygon[(i - 1) % n], 
                    polygon[i % n]))
            return 0;
    return 1;
}

/* Main function */
int main() {
    while (scanf("%d", &n) != EOF && n > 0) {
        int i;
        for (i = 0; i < n; i++)
            assert(scanf("%d %d", &polygon[i].x, &polygon[i].y) != EOF);
        printf("%s\n", is_convex() ? "No" : "Yes");
    }
    return EXIT_SUCCESS;
}
