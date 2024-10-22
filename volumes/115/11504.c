/* 11504
 * Dominos
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100000

typedef struct {
    int source, destiny;
} edge_t;

typedef struct {
    edge_t *list;
    int num_edges, component, low, visited, in_stack;
} vertex_t;

typedef struct {
    edge_t edges[MAX_N];
    vertex_t vertices[MAX_N];
    int num_vertices, num_edges;
} graph_t;

graph_t graph, dag;


/* Compare two edges */
int compare_edges(const void *a, const void *b) {
    return ((edge_t *) a)->source - ((edge_t *) b)->source;
}

/* Normalize edge list of a graph */
void normalize_edges(graph_t *g) {
    int i, e;
    qsort(g->edges, g->num_edges, sizeof (edge_t), compare_edges);
    for (i = 0, e = 0; i < g->num_vertices; i++) {
        vertex_t *v = &g->vertices[i];
        v->list = e < g->num_edges ? &g->edges[e] : NULL;
        for (v->num_edges = 0; e < g->num_edges && g->edges[e].source == i; 
                e++, v->num_edges++)
            ;
    }
}

/* Find strong component */
void find_component(graph_t *g, vertex_t *v, vertex_t *stack[], int *top, 
        int *visit_count, int *num_components) {
    int i;
    edge_t *e;

    v->visited = ++(*visit_count);
    v->low = *visit_count;
    v->in_stack = 1;
    stack[(*top)++] = v;
    for (e = v->list, i = 0; i < v->num_edges; i++, e++) {
        vertex_t *n = &g->vertices[e->destiny];
        if (!n->visited)
            find_component(g, n, stack, top, visit_count, num_components);
        if (n->in_stack && n->low < v->low)
            v->low = n->low;
    }

    if (v->low == v->visited) {
        while (*top > 0) {
            vertex_t *u = stack[--(*top)];
            u->component = *num_components;
            u->in_stack = 0;
            if (u == v)
                break;
        }
        (*num_components)++;
    }
}

/* Compute strong components for a direct graph */
int compute_components(graph_t *g) {
    vertex_t *stack[MAX_N];
    int i, top, visit_count, num_components;
    for (i = 0; i < g->num_vertices; i++)
        g->vertices[i].visited = 0;
    for (i = top = visit_count = num_components = 0; 
            i < g->num_vertices; i++) {
        vertex_t *v = &g->vertices[i];
        if (!v->visited)
            find_component(g, v, stack, &top, &visit_count, &num_components);
    }
    assert(visit_count == g->num_vertices);
    return num_components;
}

/* Generate a DAG from the strong components of a direct graph */
void create_dag(graph_t *cyclic, graph_t *acyclic) {
    int e;
    acyclic->num_vertices = compute_components(cyclic);
    acyclic->num_edges = 0;
    for (e = 0; e < cyclic->num_edges; e++) {
        edge_t *edge = &cyclic->edges[e];
        int a = cyclic->vertices[edge->source].component,
            b = cyclic->vertices[edge->destiny].component;
        if (a != b) {
            edge = &acyclic->edges[acyclic->num_edges++];
            edge->source = a;
            edge->destiny = b;
        }
    }
    /* not necessary: normalize_edges(acyclic); */
}

/* Compute number of fatherless vertices */
int compute_fatherless(graph_t *g) {
    int i, e, count;
    for (i = 0; i < g->num_vertices; i++)
        g->vertices[i].visited = 0;
    for (e = 0; e < g->num_edges; e++)
        g->vertices[g->edges[e].destiny].visited = 1;
    for (i = 0, count = 0; i < g->num_vertices; i++)
        if (!g->vertices[i].visited)
            count++;
    return count;    
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i;
        assert(scanf("%d %d", &graph.num_vertices, &graph.num_edges) != EOF);
        for (i = 0; i < graph.num_edges; i++) {
            edge_t *e = &graph.edges[i];
            assert(scanf("%d %d", &e->source, &e->destiny) != EOF);
            e->source--, e->destiny--;
        }
        normalize_edges(&graph);
        create_dag(&graph, &dag);
        printf("%d\n", compute_fatherless(&dag));
    }
    return EXIT_SUCCESS;
}


