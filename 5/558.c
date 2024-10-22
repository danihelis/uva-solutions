/* 558
 * Wormholes
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    1000
#define MAX_HOLES       2000

typedef struct {
    int source, destiny, time;
} hole_t, *hole_p;

hole_t hole[MAX_HOLES];
int num_holes, num_verices;

/* Determine whether there is a negative cycle (Bellman-Ford) */
int negative_cycle() {
    int i, h, shortest[MAX_VERTICES];
    char infinity[MAX_VERTICES];

    /* Compute shortest paths from 0 */
    memset(infinity, 1, num_verices);
    shortest[0] = 0, infinity[0] = 0;
    for (i = 0; i < num_verices - 1; i++) {
        for (h = 0; h < num_holes; h++) {
            int s = hole[h].source, d = hole[h].destiny, t = hole[h].time;
            if (!infinity[s] && (infinity[d] || shortest[s] + t < shortest[d])) {
                shortest[d] = shortest[s] + t;
                infinity[d] = 0;
            }
        }
    }

    /* Whether there is an edge whose distance is shorter than the shortest */
    for (h = 0; h < num_holes; h++) {
        int s = hole[h].source, d = hole[h].destiny, t = hole[h].time;
        if (!infinity[s] && !infinity[d] && shortest[s] + t < shortest[d]) {
            return 1;
        }
    }
    return 0;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i;
        assert(scanf("%d %d", &num_verices, &num_holes) != EOF);
        for (i = 0; i < num_holes; i++) {
            hole_p h = &hole[i];
            assert(scanf("%d %d %d", &h->source, &h->destiny, &h->time) != EOF);
        }
        printf("%spossible\n", negative_cycle() ? "" : "not ");
    }
    return 0;
}
