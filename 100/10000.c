/* 10000
 * Longest Paths
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100

typedef struct node_s {
    struct node_s *edge[MAX_N];
    int num_edges, index, visited, distance, end;
} node_t;

node_t node[MAX_N], *sorted[MAX_N];
int num_nodes, num_sorted;

/* Topological sort */
void topological_sort(node_t *n) {
    int i;
    assert(!n->visited);
    n->visited = 1;
    for (i = 0; i < n->num_edges; i++) {
        node_t *next = n->edge[i];
        if (!next->visited)
            topological_sort(next);
    }
    sorted[num_sorted++] = n;
}

/* Compute largest distances to a leaf */
void compute_distances() {
    int i, j;
    for (i = 0; i < num_sorted; i++) {
        node_t *n = sorted[i];
        for (j = 0; j < n->num_edges; j++) {
            node_t *p = n->edge[j];
            if (n->distance < p->distance + 1 || 
                    (n->distance == p->distance + 1 && 
                     p->end < n->end)) {
                n->distance = p->distance + 1;
                n->end = p->end;
            }
        }
    }
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_nodes) != EOF && num_nodes > 0) {
        int i, j, start;
        for (i = 0; i < num_nodes; i++) {
            node_t *n = &node[i];
            n->index = i + 1, n->distance = 0, n->end = i + 1;
            n->num_edges = 0, n->visited = 0;
        }
        assert(scanf("%d", &start) != EOF);
        while (scanf("%d %d", &i, &j) != EOF && i > 0) {
            i--, j--;
            node[i].edge[node[i].num_edges++] = &node[j];
        }
        num_sorted = 0;
        topological_sort(&node[--start]);
        compute_distances();
        printf("Case %d: The longest path from %d has length %d, "
                "finishing at %d.\n\n", ++test, start + 1, 
                node[start].distance, node[start].end);
    }
    return EXIT_SUCCESS;
}
