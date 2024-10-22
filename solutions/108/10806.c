/* 10806
 * Dijkstra, Dijkstra.
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define INFINITY    (1 << 30)

typedef struct node_s node_t;

typedef struct edge_s {
    node_t *destiny;
    struct edge_s *inverse;
    int length;
    char used;
} edge_t;

struct node_s {
    edge_t edge[MAX_N];
    int num_edges;
    int distance;
    edge_t *income;
};

node_t node[MAX_N];
int num_nodes;

/* Find shortest path, using Bellman-Ford's. After first pass, invert used
 * edges and negate them for minimum cost flow. No need to check cycles. */
int find_shortest_path(node_t *destiny, int mark_edges) {
    int i, j, k;
    for (i = 0; i < num_nodes; i++) {
        node_t *n = &node[i];
        n->distance = INFINITY, n->income = NULL;
    }
    node[0].distance = 0;
    /* Relax distances */
    for (k = 0; k < num_nodes - 1; k++) {
        for (i = 0; i < num_nodes; i++) {
            node_t *n = &node[i];
            for (j = 0; j < n->num_edges; j++) {
                edge_t *e = &n->edge[j];
                int distance = n->distance + e->length;
                if (e->used) continue;
                if (distance < e->destiny->distance) {
                    e->destiny->distance = distance;
                    e->destiny->income = e;
                }
            }
        }
    }
    if (destiny->distance == INFINITY) return -1;
    /* Mark used edges for next cycle */
    if (mark_edges) {
        node_t *n = destiny;
        while (n->income != NULL) {
            n->income->used = 1;
            n->income->inverse->length *= -1;
            n = n->income->inverse->destiny;
        }
    } 
    return destiny->distance;
}

/* Read graph */
void read_graph() {
    int i, num_edges;
    for (i = 0; i < num_nodes; i++) {
        node[i].num_edges = 0;
    }
    assert(scanf("%d", &num_edges) != EOF);
    while (num_edges-- > 0) {
        int a, b, length;
        node_t *na, *nb;
        edge_t *ea, *eb;
        assert(scanf("%d %d %d", &a, &b, &length) != EOF);
        na = &node[--a], nb = &node[--b];
        ea = &na->edge[na->num_edges++], eb = &nb->edge[nb->num_edges++];
        ea->destiny = nb, ea->inverse = eb;
        eb->destiny = na, eb->inverse = ea;
        ea->length = eb->length = length;
        ea->used = eb->used = 0;
    }
}

/* Main function */
int main() {
    while (scanf("%d", &num_nodes) > 0 && num_nodes > 0) {
        int distance, total_distance = 0;
        node_t *destiny = &node[num_nodes - 1];
        read_graph();
        distance = find_shortest_path(destiny, 1);
        if (distance != -1) {
            total_distance = distance;
            distance = find_shortest_path(destiny, 0);
            total_distance += distance;
        }
        if (distance == -1) printf("Back to jail\n");
        else printf("%d\n", total_distance);
    }
    return EXIT_SUCCESS;
}
