/* 10301
 * Rings and Glue
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_RINGS 100

typedef struct ring_s {
    struct ring_s *set;
    int count;
    double x, y, radius;
} ring_t, *ring_p;

ring_t ring[MAX_RINGS];
int num_rings;

/* Find the set containing the ring */
ring_p find_set(ring_p ring) {
    if (ring != ring->set) {
        ring->set = find_set(ring->set);
    }
    return ring->set;
}

/* Join two ring sets together */
void join(ring_p a, ring_p b) {
    ring_p set_a = find_set(a), set_b = find_set(b);
    if (set_a != set_b) {
        set_a->set = set_b;
    }
}

/* Whether two rings intercept one another */
#define SQUARE(x) ((x) * (x))
#define ABS_DIFF(x, y) ((x) > (y) ? (x) - (y) : (y) - (x))
int intercept(ring_p a, ring_p b) {
    double distance = sqrt(SQUARE(a->x - b->x) + SQUARE(a->y - b->y));
    return (distance < a->radius + b->radius && distance > ABS_DIFF(a->radius, b->radius));
}

/* Main function */
int main() {
    while (scanf("%d", &num_rings) != EOF && num_rings != -1) {
        int i, j;
        ring_p largest;
        if (num_rings == 0) {
            printf("The largest component contains 0 rings.\n");
            continue;
        }
        for (i = 0; i < num_rings; i++) {
            assert(scanf("%lf %lf %lf", &ring[i].x, &ring[i].y, &ring[i].radius) != EOF);
            ring[i].count = 0;
            ring[i].set = &ring[i];
        }
        for (i = 0; i < num_rings - 1; i++) {
            for (j = i + 1; j < num_rings; j++) {
                if (intercept(&ring[i], &ring[j])) {
                    join(&ring[i], &ring[j]);
                }
            }
        }
        for (i = 0, largest = &ring[0]; i < num_rings; i++) {
            ring_p set = find_set(&ring[i]);
            set->count++;
            if (set->count > largest->count) {
                largest = set;
            }
        }
        printf("The largest component contains %d ring%s.\n", largest->count, 
                (largest->count == 1 ? "" : "s"));
    }
    return 0;
}
