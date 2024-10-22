/* 539
 * The Settlers of Catan
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       25
#define UNVISITED   0

typedef struct {
    int a, b, visited;
} edge_t;

typedef struct {
    edge_t *edge[MAX_N];
    int num_edges;
} node_t;

edge_t edge[MAX_N];
node_t node[MAX_N];
int num_nodes, num_edges;

/* Find largest path from node */
int largest_path(int n) {
    int i, cost, max_cost;
    for (i = max_cost = 0; i < node[n].num_edges; i++) {
        edge_t *e = node[n].edge[i];
        if (!e->visited) {
            e->visited = 1;
            cost = 1 + largest_path(e->a == n ? e->b : e->a);
            e->visited = 0;
            if (cost > max_cost)
                max_cost = cost;
        }
    }
    return max_cost;
}

/* Main function */
#define ADD_EDGE(n, e)     (node[n].edge[node[n].num_edges++] = (e))
int main() {
    while (scanf("%d %d", &num_nodes, &num_edges) == 2 && num_nodes > 0) {
        int i, cost, max_cost;
        for (i = 0; i < num_nodes; i++)
            node[i].num_edges = 0;
        for (i = 0; i < num_edges; i++) {
            edge_t *e = &edge[i];
            assert(scanf("%d %d", &e->a, &e->b) == 2);
            e->visited = 0;
            ADD_EDGE(e->a, e);
            ADD_EDGE(e->b, e);
        }
        for (i = max_cost = 0; i < num_nodes; i++)
            if ((cost = largest_path(i)) > max_cost)
                max_cost = cost;
        printf("%d\n", max_cost);
    }
    return EXIT_SUCCESS;
}
