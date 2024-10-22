/* 920
 * Sunny Mountains
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COORD   100

typedef struct {
    int x, y;
} point_t;

/* Compare two points */
int compare(const void *a, const void *b) {
    return ((point_t *) a)->x - ((point_t *) b)->x;
}

/* Get x coordenate from intersection between mountain side and sun beam */
double get_x(point_t *a, point_t *b, int y) {
    double alpha = (y - a->y) / (double) (b->y - a->y);
    return a->x + alpha * (b->x - a->x);
}

/* Get distance between two points (side length) */
double get_distance(point_t *a, double x, int y) {
    return sqrt((a->y - y) * (a->y - y) + (a->x - x) * (a->x - x));
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, n, last_height;
        double distance;
        point_t point[MAX_COORD];
        assert(scanf("%d", &n) != EOF);
        for (i = 0; i < n; i++)
            assert(scanf("%d %d", &point[i].x, &point[i].y) != EOF);
        qsort(point, n, sizeof (point_t), compare);
        assert(point[n - 1].y == 0);
        for (i = n - 2, distance = 0, last_height = 0; i >= 0; i--)
            if (point[i].y > last_height) {
                double x = get_x(&point[i], &point[i + 1], last_height);
                distance += get_distance(&point[i], x, last_height);
                last_height = point[i].y;
            }
        printf("%.2f\n", distance);
    }
    return EXIT_SUCCESS;
}
