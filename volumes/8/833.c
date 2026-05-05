/* 833
 * Water Falls
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEGS        10000
#define EQUALS(a,b)     ((a).x == (b).x && (a).y == (b).y)

typedef struct {
    int x, y;
} point_t;

typedef struct {
    point_t p1, p2;
} segment_t;

segment_t segments[MAX_SEGS];
int num_segments;


/* Determine the next point of a water flow dropping from point P */
point_t find_next_drop(point_t p) {
    int i;
    double cross = 0;
    segment_t *highest = NULL;

    for (i = 0; i < num_segments; i++) {
        segment_t *seg = &segments[i];
        if (EQUALS(p, seg->p1) || EQUALS(p, seg->p2)) continue;
        if (p.x >= seg->p1.x && p.x <= seg->p2.x) {
            double alpha = (p.x - seg->p1.x) / (double) (seg->p2.x - seg->p1.x);
            double y = seg->p1.y + alpha * (seg->p2.y - seg->p1.y);
            if (y <= p.y && y > cross) cross = y, highest = seg;
        }
    }
    if (highest == NULL) p.y = 0;
    else p = highest->p1.y < highest->p2.y ? highest->p1 : highest->p2;
    return p;
}


/* Find last X-coord of flow dropping from point p */
int find_last_drop(point_t p) {
    while (p.y > 0) {
        p = find_next_drop(p);
    }
    return p.x;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        int i, num_points;

        assert(scanf("%d", &num_segments) == 1);
        for (i = 0; i < num_segments; i++) {
            segment_t *s = &segments[i];
            assert(scanf("%d %d %d %d", &s->p1.x, &s->p1.y, &s->p2.x, &s->p2.y)
                    == 4);
            if (s->p1.x > s->p2.x) {
                point_t swap = s->p1;
                s->p1 = s->p2;
                s->p2 = swap;
            }
        }

        assert(scanf("%d", &num_points) == 1);
        while (num_points-- > 0) {
            point_t p;
            assert(scanf("%d %d", &p.x, &p.y) == 2);
            printf("%d\n", find_last_drop(p));
        }

        if (num_tests > 0) printf("\n");
    }

    return EXIT_SUCCESS;
}
