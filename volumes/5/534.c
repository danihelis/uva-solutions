/* 534
 * Frogger
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_V       200
#define MAX_E       (MAX_V * MAX_V)
#define SQ(x)       ((x) * (x))

typedef struct {
    int x, y;
} point_t;

typedef struct {
    int a, b;
    long distance;
} edge_t;

typedef void *set_t;

point_t point[MAX_V];
edge_t edge[MAX_E];
set_t set[MAX_V];
int num_vertices, num_edges;

/* Get set */
set_t get_set(set_t *s) {
    if (*s != s)
        *s = get_set(*s);
    return *s;
}

/* Join sets */
void join_sets(set_t *a, set_t *b) {
    a = get_set(a);
    *a = get_set(b);
}

/* Compare edges */
int compare(const void *a, const void *b) {
    return ((edge_t *) a)->distance < ((edge_t *) b)->distance ? -1 : 1;
}

/* Find longest edge from MST */
double get_mst_longest_edge() {
    int i, j;
    for (i = num_edges = 0; i < num_vertices; i++) {
        set[i] = &set[i];
        for (j = i + 1; j < num_vertices; j++) {
            edge_t *e = &edge[num_edges++];
            e->a = i, e->b = j;
            e->distance = SQ(point[i].x - point[j].x) + 
                    SQ(point[i].y - point[j].y);
        }
    }
    qsort(edge, num_edges, sizeof (edge_t), compare);
    for (i = 0; i < num_edges && get_set(&set[0]) != get_set(&set[1]); i++) {
        edge_t *e = &edge[i];
        join_sets(&set[e->a], &set[e->b]);
    }
    assert(i > 0 && i <= num_edges);
    return sqrt(edge[i - 1].distance);
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_vertices) == 1 && num_vertices > 0) {
        int i;
        for (i = 0; i < num_vertices; i++) {
            point_t *p = &point[i];
            assert(scanf("%d %d", &p->x, &p->y) == 2);
        }
        printf("Scenario #%d\nFrog Distance = %.3f\n\n", ++test,
                get_mst_longest_edge());
    }
    return EXIT_SUCCESS;
}
