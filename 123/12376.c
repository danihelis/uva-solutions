/* 12376
 * As Long as I Learn, I Live
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES       100

typedef struct node_s {
    struct node_s *next[MAX_NODES];
    int num_links, value;
} node_t, *node_p;

node_t graph[MAX_NODES];

/* Compute the maximum path along the graph */
int maximum_path(node_p *last) {
    int sum = 0;
    node_p node = &graph[0];
    while (node->num_links > 0) {
        int i;
        node_p best = node->next[0];
        for (i = 1; i < node->num_links; i++) {
            if (node->next[i]->value > best->value) {
                best = node->next[i];
            }
        }
        node = best;
        sum += node->value;
    }
    *last = node;
    return sum;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        node_p node;
        int total, num_nodes, num_edges, i;
        assert(scanf("%d %d", &num_nodes, &num_edges) != EOF);
        for (i = 0; i < num_nodes; i++) {
            assert(scanf("%d", &graph[i].value) != EOF);
            graph[i].num_links = 0;
        }
        for (i = 0; i < num_edges; i++) {
            int x, y;
            assert(scanf("%d %d", &x, &y) != EOF);
            node = &graph[x];
            node->next[node->num_links++] = &graph[y];
        }
        total = maximum_path(&node);
        printf("Case %d: %d %ld\n", test, total, (node - graph));
    }
    return 0;
}
