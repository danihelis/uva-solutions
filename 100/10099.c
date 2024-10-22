/* 10099
 * The Tourist Guide
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    100
#define MAX_EDGES       (MAX_VERTICES * MAX_VERTICES)
#define INFTY           (1 << 31)

typedef void * set_t;

typedef struct {
    int a, b, cost;
} edge_t;

set_t vertex[MAX_VERTICES];
edge_t edge[MAX_EDGES];
int num_vertices, num_edges;

/* Compare two edges in descending order */
int compare_edge(const void *a, const void *b) {
    return ((edge_t *) b)->cost - ((edge_t *) a)->cost;
}

/* Get set */
set_t set(set_t *s) {
    if (*s == s)
        return s;
    return (*s = set(*s));
}

/* Join sets */
void join(set_t *a, set_t *b) {
    a = set(a);
    *a = set(b);
}

/* Maximum spanning tree to connect two cities */
int max_tree(int start, int end) {
    int i, capacity;
    set_t *vs = &vertex[start], *ve = &vertex[end];
    for (i = 0; i < num_vertices; i++)
        vertex[i] = &vertex[i];
    qsort(edge, num_edges, sizeof (edge_t), compare_edge);
    for (i = 0, capacity = INFTY; set(vs) != set(ve) && i < num_edges; i++) {
        edge_t *e = &edge[i];
        set_t *va = &vertex[e->a], *vb = &vertex[e->b];
        if (set(va) != set(vb))
            capacity = e->cost, join(va, vb);
    }
    return capacity;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d %d", &num_vertices, &num_edges) != EOF && 
            num_vertices > 0) {
        int i, start, end, passengers, cost;
        for (i = 0; i < num_edges; i++) {
            edge_t *e = &edge[i];
            assert(scanf("%d %d %d", &e->a, &e->b, &e->cost) != EOF);
            e->a--, e->b--;
        }
        assert(scanf("%d %d %d", &start, &end, &passengers) != EOF);
        cost = max_tree(--start, --end) - 1;
        assert(cost > 0);
        printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", ++test,
                (passengers + cost - 1) / cost);
    }
    return EXIT_SUCCESS;
}
