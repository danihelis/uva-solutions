/* 1208
 * Oreon
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES    26
#define MAX_EDGES       (MAX_VERTICES * MAX_VERTICES / 2)

typedef struct {
    int source, destiny, weight;
} edge_t;

int set[MAX_VERTICES];
int weight[MAX_VERTICES][MAX_VERTICES];
int num_vertices;
edge_t mst[MAX_VERTICES];

/* Get set for vertex */
int get_set(int vertex) {
    if (set[vertex] == vertex) return vertex;
    set[vertex] = get_set(set[vertex]);
    return set[vertex];
}

/* Join two sets */
int join_sets(int a, int b) {
    a = get_set(a), b = get_set(b);
    set[a] = b;
    return b;
}

/* Compare edges by weight */
int compare(const void *a, const void *b) {
    edge_t *x = (edge_t *) a, *y = (edge_t *) b;
    if (x->weight == y->weight) return x->source - y->source;
    return x->weight - y->weight;
}

/* Computes minimal spanning tree */
int compute_mst() {
    edge_t edges[MAX_EDGES];
    int a, b, i, num_edges, mst_size;

    for (a = num_edges = 0; a < num_vertices; a++) {
        set[a] = a;
        for (b = a + 1; b < num_vertices; b++) {
            if (weight[a][b]) {
                edge_t *e = &edges[num_edges++];
                e->source = a, e->destiny = b, e->weight = weight[a][b];
            }
        }
    }
    qsort(edges, num_edges, sizeof (edge_t), compare);

    mst_size = 0, i = 0;
    while (mst_size < num_vertices - 1 && i < num_edges) {
        edge_t *e = &edges[i++];
        if (get_set(e->source) != get_set(e->destiny)) {
            mst[mst_size++] = *e;
            join_sets(e->source, e->destiny);
        }
    }
    return mst_size;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int a, b, size;

        assert(scanf("%d", &num_vertices) == 1);
        for (a = 0; a < num_vertices; a++) {
            for (b = 0; b < num_vertices; b++) {
                assert(scanf(b == 0 ? "%d" : ", %d", &weight[a][b]) == 1);
            }
        }

        size = compute_mst();
        printf("Case %d:\n", test);
        for (a = 0; a < size; a++) {
            edge_t *e = &mst[a];
            printf("%c-%c %d\n", 'A' + e->source, 'A' + e->destiny, e->weight);
        }
    }
    return EXIT_SUCCESS;
}
