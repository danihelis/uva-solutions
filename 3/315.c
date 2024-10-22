/* 315
 * Network
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE        1000
#define NUM_CONNECTION  2
#define MAX_NODES       100
#define MAX_EDGES       (MAX_NODES * MAX_NODES)
#define NOT_VISITED     -1

#define MIN(x, y)       (x < y ? x : y)

struct node_s;
typedef struct edge_s {
    struct node_s *node[NUM_CONNECTION];
    char visited;
} edge_t, *edge_p;

typedef struct node_s {
    edge_p edge[MAX_NODES];
    int num_edges;
    int index, component;
    char is_articulation;
} node_t, *node_p;

edge_t edge[MAX_EDGES];
node_t node[MAX_NODES];
int num_edges, num_nodes;

#define NEIGHBOUR(v, e)     ((e)->node[0] != (v) ? e->node[0] : e->node[1])

/* Find a node's component using depth-first search */
int find_compontent(node_p node, int index, char is_root) {
    int e, count;
    node->index = index;
    node->component = index;
    node->is_articulation = 0;
    for (e = 0, count = 0; e < node->num_edges; e++) {
        edge_p edge = node->edge[e];
        if (edge->visited == NOT_VISITED) {
            node_p neigh = NEIGHBOUR(node, edge);
            edge->visited = 1;
            if (neigh->index != NOT_VISITED) {
                node->component = MIN(node->component, neigh->index);
            }
            else {
                index = find_compontent(neigh, index + 1, 0);
                count++;
                node->is_articulation |= (neigh->component >= node->index);
                node->component = MIN(node->component, neigh->component);
            }

        }
    }
    if (is_root) {
        node->is_articulation = (count > 1);
    }
    return index;
}

/* Compute total number of articulation points */
int compute_articulations() {
    int total, i, count;
    for (i = 0, total = 0, count = 0; i < num_nodes; i++) {
        node_p root = &node[i];
        if (root->index == NOT_VISITED) {
            count = find_compontent(root, count, 1);
        }
        total += (root->is_articulation ? 1 : 0);
    }
    return total;
}

/* Main function */
#define READ(s)             (fgets(s, MAX_LINE, stdin) != NULL)
#define ADD_EDGE(e, v, n)   (e)->node[n] = &node[v]; node[v].edge[node[v].num_edges++] = (e)
int main() {
    char line[MAX_LINE];
    while (READ(line) && (num_nodes = atoi(line)) > 0) {
        int i;
        for (i = 0; i < num_nodes; i++) {
            node[i].index = NOT_VISITED;
            node[i].num_edges = 0;
        }
        num_edges = 0;
        while (i > 0) {
            char *token;
            assert(READ(line));
            token = strtok(line, " ");
            i = atoi(token);
            if (i > 0) {
                token = strtok(NULL, " ");
                while (token != NULL) {
                    int j = atoi(token);
                    if (j > 0) {
                        edge_p new_edge = &edge[num_edges++];
                        new_edge->visited = NOT_VISITED;
                        ADD_EDGE(new_edge, i - 1, 0);
                        ADD_EDGE(new_edge, j - 1, 1);
                    }
                    token = strtok(NULL, " ");
                }
            }
        }
        printf("%d\n", compute_articulations());
    }
    return 0;
}
