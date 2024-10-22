/* 796
 * Critical Links
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    1000
#define MAX_EDGES       (MAX_VERTICES * MAX_VERTICES)
#define NO_INDEX        -1

typedef struct vertex_s vertex_t, *vertex_p;

typedef struct {
    vertex_p vertex[2];
    char visited, bridge;
} edge_t, *edge_p;

struct vertex_s {
    edge_p edge[MAX_VERTICES];
    int num_edges, index, component;
};

edge_t edge[MAX_EDGES], *ptr_edge[MAX_EDGES];
vertex_t vertex[MAX_VERTICES];
int num_edges, num_vertices;

#define NEIGHBOUR(v, e)     ((e)->vertex[0] == (v) ? (e)->vertex[1] : (e)->vertex[0])
#define MIN(x, y)           ((x) < (y) ? (x) : (y))
#define MAX(x, y)           ((x) > (y) ? (x) : (y))


/* Compare two edges */
int compare_edge(const void *a, const void *b) {
    edge_p x = *((edge_p *) a), y = *((edge_p *) b);
    return (x->vertex[0] == y->vertex[0] ? x->vertex[1] - y->vertex[1] : 
            x->vertex[0] - y->vertex[0]);
}

/* Define the component of vertices through DPS */
int define_component(vertex_p vertex, int index) {
    int e;
    vertex->index = index;
    vertex->component = index;
    for (e = 0; e < vertex->num_edges; e++) {
        edge_p edge = vertex->edge[e];
        if (!edge->visited) {
            vertex_p neigh = NEIGHBOUR(vertex, edge);
            edge->visited = 1;
            if (neigh->index == NO_INDEX) {
                index = define_component(neigh, index + 1);
                vertex->component = MIN(vertex->component, neigh->component);
            }
            else {
                vertex->component = MIN(vertex->component, neigh->index);
            }
        }
    }
    return index;
}

/* Define all components of the graph and compute the bridges */
int compute_bridges() {
    int i, count;
    for (i = 0, count = 0; i < num_vertices; i++) {
        if (vertex[i].index == NO_INDEX) {
            count = define_component(&vertex[i], count + 1);
        }
    }
    for (i = 0, count = 0; i < num_edges; i++) {
        vertex_p v0 = edge[i].vertex[0], v1 = edge[i].vertex[1];
        edge[i].bridge = (v0->index < v1->component) || (v1->index < v0->component);
        count += (edge[i].bridge ? 1 : 0);
        ptr_edge[i] = &edge[i];
    }
    qsort(ptr_edge, num_edges, sizeof (edge_p), compare_edge);
    return count;
}

/* Main function */
#define ADD_EDGE(v, e)      ((v)->edge[(v)->num_edges++] = (e))
int main() {
    while (scanf("%d", &num_vertices) != EOF) {
        int i, j, v, n, e;
        edge_p bridge;
        for (i = 0; i < num_vertices; i++) {
            vertex[i].num_edges = 0, vertex[i].index = NO_INDEX;
        }
        for (i = 0, num_edges = 0; i < num_vertices; i++) {
            assert(scanf("%d (%d)", &v, &n) != EOF);
            for (j = 0; j < n; j++) {
                assert(scanf("%d", &e) != EOF);
                if (v < e) {
                    bridge = &edge[num_edges++];
                    bridge->visited = 0;
                    bridge->vertex[0] = &vertex[v], bridge->vertex[1] = &vertex[e];
                    ADD_EDGE(&vertex[v], bridge), ADD_EDGE(&vertex[e], bridge);
                }
            }
        }
        printf("%d critical links\n", compute_bridges());
        for (i = 0; i < num_edges; i++) {
            bridge = ptr_edge[i];
            if (bridge->bridge) {
                printf("%ld - %ld\n", bridge->vertex[0] - vertex, bridge->vertex[1] - vertex);
            }
        }
        printf("\n");
    }
    return 0;
}
