/* 11747
 * Heavy Cycle Edges
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_EDGES       25000
#define MAX_VERTICES    1000

typedef struct {
    int a, b, weight;
} edge_t;

edge_t edge[MAX_EDGES];
int set[MAX_VERTICES];
int num_edges, num_vertices;

/* Get set */
int get_set(int v) {
    if (set[v] == v)
        return v;
    set[v] = get_set(set[v]);
    return set[v];
}

/* Compare edges */
int compare(const void *a, const void *b) {
    return ((edge_t *) a)->weight - ((edge_t *) b)->weight;
}

/* Kruskal's minimum spanning tree */
void mst() {
    int i, count;
    qsort(edge, num_edges, sizeof (edge_t), compare);
    for (i = 0; i < num_vertices; i++)
        set[i] = i;
    for (i = 0, count = 0; i < num_edges; i++) {
        edge_t *e = &edge[i];
        int s1 = get_set(e->a), s2 = get_set(e->b);
        if (s1 == s2)
            printf("%s%d", count++ == 0 ? "" : " ", e->weight);
        else
            set[s1] = s2;
    }
    printf("%s\n", count == 0 ? "forest" : "");
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_vertices, &num_edges) != EOF && 
            num_vertices > 0) {
        int i;
        for (i = 0; i < num_edges; i++) {
            edge_t *e = &edge[i];
            assert(scanf("%d %d %d", &e->a, &e->b, &e->weight) != EOF);
        }
        mst();
    }
    return EXIT_SUCCESS;
}
