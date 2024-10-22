/* 11800
 * Determine the Shape
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_POINTS 4
#define NUM_DISTANCES 3
#define SQUARE(x) ((x) * (x))
#define DISTANCE(p, q) (SQUARE((p).x - (q).x) + SQUARE((p).y - (q).y))
#define CREATE_VECTOR(v, p, q) (v).x = (p).x - (q).x, (v).y = (p).y - (q).y
#define DOT_PRODUCT(r, s) ((r).x * (s).x + (r).y * (s).y)
#define NORM(v) (SQUARE((v).x) + SQUARE((v).y))

typedef struct {
    long x, y;
} point_t, pair_t;

pair_t pair[NUM_DISTANCES * 2] = {{0, 1}, {2, 3}, {0, 2}, {1, 3}, {0, 3}, {1, 2}};

/* Main function */
int main() {
    int i, test, num_tests;
    point_t point[NUM_POINTS];
    long distance[NUM_DISTANCES];
    int equal_sides, equal_pairs;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        printf("Case %d: ", test);
        for (i = 0; i < NUM_POINTS; i++) {
            assert(scanf("%ld %ld", &point[i].x, &point[i].y) != EOF);
        }
        equal_sides = 0;
        for (i = 0; i < NUM_DISTANCES; i++) {
            long first = DISTANCE(point[pair[2 * i].x], point[pair[2 * i].y]);
            long second = DISTANCE(point[pair[2 * i + 1].x], point[pair[2 * i + 1].y]);
            distance[i] = - i - 1;
            if (first == second) {
                equal_sides++;
                distance[i] = first;
            }
        }
        equal_pairs = (distance[0] == distance[1] ? 1 : 0) + (distance[0] == distance[2] ? 1 : 0)
                + (distance[1] == distance[2] ? 1 : 0);
        if (equal_sides == 3) {
            printf("%s\n", (equal_pairs > 0 ? "Square" : "Rectangle"));
        }
        else if (equal_sides == 2 && equal_pairs > 0) {
            printf("Rhombus\n");
        }
        else {
            int parallels = 0;
            for (i = 0; i < NUM_DISTANCES; i++) {
                point_t v1, v2;
                long n1, n2;
                CREATE_VECTOR(v1, point[pair[2 * i].x], point[pair[2 * i].y]);
                CREATE_VECTOR(v2, point[pair[2 * i + 1].x], point[pair[2 * i + 1].y]);
                n1 = NORM(v1), n2 = NORM(v2);
                if (SQUARE(DOT_PRODUCT(v1, v2)) == n1 * n2) {
                    parallels++;
                }
            }
            printf("%s\n", (parallels == 2 ? "Parallelogram" : parallels == 1 ? "Trapezium" : 
                        "Ordinary Quadrilateral"));
        }
    }
    return 0;
}
