/* 10397
 * Connect the Campus
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES        750
#define MAX_EDGES           (MAX_VERTICES * MAX_VERTICES)
#define SQ(x)               ((x) * (x))

typedef struct vertex_s {
    int x, y;
    struct vertex_s *set;
    int rank;
} vertex_t;

typedef struct {
    int dist;
    vertex_t *a, *b;
} edge_t;

vertex_t vertex[MAX_VERTICES];
edge_t edge[MAX_EDGES], *edge_v[MAX_EDGES];
int num_vertices, num_edges;

/* Get set */
vertex_t * get_set(vertex_t *v) {
    if (v->set != v)
        v->set = get_set(v->set);
    return v->set;
}

/* Join sets (using ranks, which doesn't improve time significantly) */
void join_sets(vertex_t *a, vertex_t *b) {
    /*
    vertex_t *head = get_set(a->set);
    head->set = get_set(b->set);
    */
    a = get_set(a), b = get_set(b);
    if (a->rank > b->rank)
        b->set = a;
    else {
        a->set = b;
        if (a->rank == b->rank)
            b->rank++;
    }
}

/* Whether all vertices are connected */
int is_connected() {
    int i;
    vertex_t *head = get_set(&vertex[0]);
    for (i = 1; i < num_vertices; i++)
        if (get_set(&vertex[i]) != head)
            return 0;
    return 1;
}

/* Compare two edges */
int compare_edges(const void *a, const void *b) {
    edge_t *x = * (edge_t **) a, *y = * (edge_t **) b;
    return x->dist - y->dist;
}

/* Create MST with new connections */
double mst() {
    double cost;
    int i;
    qsort(edge_v, num_edges, sizeof (edge_t *), compare_edges);
    for (i = 0, cost = 0; i < num_edges; i++) {
        edge_t *e = edge_v[i];
        if (get_set(e->a) != get_set(e->b)) {
            join_sets(e->a, e->b);
            cost += sqrt(e->dist);
            if (is_connected())
                break;
        }
    }
    return cost;
}

/* Main function */
int main() {
    while (scanf("%d", &num_vertices) == 1) {
        int i, j, k;
        for (i = 0; i < num_vertices; i++) {
            vertex_t *v = &vertex[i];
            assert(scanf("%d %d", &v->x, &v->y) == 2);
            v->set = v, v->rank = 0;
        }
        assert(scanf("%d", &k) == 1);
        for (; k > 0; k--) {
            assert(scanf("%d %d", &i, &j) == 2);
            join_sets(&vertex[--i], &vertex[--j]);
        }
        for (i = num_edges = 0; i < num_vertices - 1; i++)
            for (j = i + 1; j < num_vertices; j++) {
                vertex_t *a = &vertex[i], *b = &vertex[j];
                if (get_set(a) != get_set(b)) {
                    edge_t *e = &edge[num_edges];
                    e->a = a, e->b = b;
                    e->dist = SQ(a->x - b->x) + SQ(a->y - b->y);
                    edge_v[num_edges++] = e;
                }
            }
        printf("%.2f\n", mst());
    }
    return EXIT_SUCCESS;
}
