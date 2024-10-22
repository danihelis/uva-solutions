/* 821
 * Page Hopping
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   100
#define INFINITY    (1 << 20)

typedef struct node_s {
    int index, counter;
    struct node_s *edge[MAX_NODES];
    int num_edges;
} node_t;

node_t node[MAX_NODES], *p_node[MAX_NODES];
int num_nodes;

/* Find node or insert */
node_t * find_or_insert(int index) {
    int start = 0, end = num_nodes;
    while (start < end) {
        int middle = (start + end) / 2;
        if (p_node[middle]->index == index)
            return p_node[middle];
        else if (p_node[middle]->index > index)
            end = middle;
        else 
            start = middle + 1;
    }
    for (end = num_nodes; end > start; end--)
        p_node[end] = p_node[end - 1];
    p_node[start] = &node[num_nodes++];
    p_node[start]->counter = num_nodes - 1;
    p_node[start]->index = index;
    p_node[start]->num_edges = 0;
    return p_node[start];
}

/* Compute all distances between nodes, and return average */
double compute_average_distance() {
    int distance[MAX_NODES][MAX_NODES];
    int i, j, k, sum;

    for (i = 0; i < num_nodes; i++) {
        node_t *n = p_node[i];
        for (j = 0; j < num_nodes; j++)
            distance[n->counter][j] = (n->counter == j ? 0 : INFINITY);
        for (j = 0; j < n->num_edges; j++) {
            distance[n->counter][n->edge[j]->counter] = 1;
        }
    }
    for (k = 0; k < num_nodes; k++)
        for (i = 0; i < num_nodes; i++)
            for (j = 0; j < num_nodes; j++) {
                int shortcut = distance[i][k] + distance[k][j];
                if (distance[i][j] > shortcut)
                    distance[i][j] = shortcut;
            }

    for (i = 0, sum = 0; i < num_nodes; i++)
        for (j = 0; j < num_nodes; j++)
            sum += distance[i][j];
    return sum / (double) (num_nodes * (num_nodes - 1));
}

/* Main function */
int main() {
    int a, b, test = 0;
    while (scanf("%d %d", &a, &b) != EOF && a > 0) {
        num_nodes = 0;
        do {
            node_t *na = find_or_insert(a), *nb = find_or_insert(b);
            na->edge[na->num_edges++] = nb;
            assert(scanf("%d %d", &a, &b) != EOF);
        } while (a > 0);
        printf("Case %d: average length between pages = %.3f clicks\n",
                ++test, compute_average_distance());
    }
    return EXIT_SUCCESS;
}
