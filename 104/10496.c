/* 10496
 * Collecting Beepers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BEEPERS     10
#define ABS_DIFF(x,y)   ((x) > (y) ? (x) - (y) : (y) - (x))
#define DISTANCE(p1,p2) (ABS_DIFF((p1).x, (p2).x) + ABS_DIFF((p1).y, (p2).y))
#define INFINITE        (MAX_BEEPERS * 1000)

typedef struct {
    int x, y;
    char used;
} point_t, *point_p;

point_t origin, beeper[MAX_BEEPERS];
int num_beepers, min_path;

/* Compute the shortest path to collect all beepers and return to start position */
void compute_shortest_path(int order, int size, point_p last) {
    if (order >= num_beepers) {
        int total = size + DISTANCE(*last, origin);
        if (total < min_path) {
            min_path = total;
        }
    }
    else {
        int i;
        for (i = 0; i < num_beepers; i++) {
            point_p next = &beeper[i];
            if (!next->used) {
                int dist = size + DISTANCE(*last, *next);
                if (dist < min_path) {
                    next->used = 1;
                    compute_shortest_path(order + 1, dist, next);
                    next->used = 0;
                }
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests, i;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%*d %*d %d %d %d", &origin.x, &origin.y, &num_beepers) != EOF);
        for (i = 0; i < num_beepers; i++) {
            assert(scanf("%d %d", &beeper[i].x, &beeper[i].y) != EOF);
            beeper[i].used = 0;
        }
        min_path = INFINITE;
        compute_shortest_path(0, 0, &origin);
        assert(min_path < INFINITE);
        printf("The shortest path has length %d\n", min_path);
    }
    return 0;
}
