/* 10600
 * ACM Contest and Blackout
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    100
#define MAX_EDGES       (MAX_VERTICES * MAX_VERTICES)
#define INFINITY        3000

typedef struct vertex_s vertex_t;

typedef struct {
    vertex_t *v1, *v2;
    int cost, used, visited;
} edge_t;

struct vertex_s {
    edge_t *edges[MAX_VERTICES];
    int num_edges;
    vertex_t *set;
};

edge_t edges[MAX_EDGES], *ptr_edges[MAX_EDGES];
vertex_t vertices[MAX_VERTICES];
int num_edges, num_vertices;

/* Compare two edge pointers by cost */
int compare_edges(const void *a, const void *b) {
    return (* (edge_t **) a)->cost - (* (edge_t **) b)->cost;
}

/* Find set */
vertex_t * find_set(vertex_t *v) {
    if (v->set == v)
        return v;
    v->set = find_set(v->set);
    return v->set;
}

/* Join sets */
void join_sets(vertex_t *v1, vertex_t *v2) {
    v1 = find_set(v1);
    v1->set = find_set(v2);
}

/* Find cheapest used edge between two vertices */
int find_cheapest_edge_exchange(edge_t *edge) {
    struct {
        vertex_t *vertex;
        int last_edge;
        int cost;
    } stack[MAX_VERTICES], *elem;
    int i, found, top = 1;

    for (i = 0; i < num_edges; i++)
        edges[i].visited = 0;

    stack[0].vertex = edge->v1;
    stack[0].last_edge = 0;

    while (top > 0) {
        elem = &stack[top - 1];
        if (elem->vertex == edge->v2) {
            int most_expensive;
            for (most_expensive = 0, i = top - 1; i > 0; i--)
                if (stack[i].cost > most_expensive)
                    most_expensive = stack[i].cost;
            return edge->cost - most_expensive;
        }
        for (found = 0; !found && elem->last_edge < elem->vertex->num_edges; 
                elem->last_edge++) {
            edge_t *e = elem->vertex->edges[elem->last_edge];
            if (e->used && !e->visited) {
                e->visited = 1;
                stack[top].vertex = e->v1 == elem->vertex ? e->v2 : e->v1;
                stack[top].last_edge = 0;
                stack[top].cost = e->cost;
                top++, found = 1;
            }
        }
        if (!found)
            top--;
    }
    assert(NULL); /* could not find path */
    return 0;
}

/* Find minimum spanning tree and second minimum as well */
void find_mst(int *minimum, int *second_mininum) {
    int i, edges_used, total_cost, exchange; 

    for (i = 0; i < num_edges; i++) {
        ptr_edges[i] = &edges[i];
        ptr_edges[i]->used = ptr_edges[i]->visited = 0;
    }
    qsort(ptr_edges, num_edges, sizeof (edge_t *), compare_edges);

    for (i = 0; i < num_vertices; i++)
        vertices[i].set = &vertices[i];

    total_cost = 0;
    edges_used = 0;
    for (i = 0; i < num_edges && edges_used < num_vertices - 1; i++) {
        edge_t *e = ptr_edges[i];
        vertex_t *v1 = find_set(e->v1), *v2 = find_set(e->v2);
        if (v1 != v2) {
            join_sets(v1, v2);
            e->used = 1;
            total_cost += e->cost;
            edges_used++;
        }
    }
    for (i = 0, exchange = -1; i < num_edges && exchange != 0; i++) {
        edge_t *e = ptr_edges[i];
        if (!e->used) {
            int diff = find_cheapest_edge_exchange(e);
            if (exchange < 0 || diff < exchange)
                exchange = diff;
        }
    }

    *minimum = total_cost;
    *second_mininum = total_cost + exchange;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, minimum, second_mininum;
        assert(scanf("%d %d", &num_vertices, &num_edges) != EOF);
        for (i = 0; i < num_vertices; i++)
            vertices[i].num_edges = 0;
        for (i = 0; i < num_edges; i++) {
            int a, b, c;
            edge_t *e = &edges[i];
            assert(scanf("%d %d %d", &a, &b, &c) != EOF);
            e->v1 = &vertices[--a];
            e->v2 = &vertices[--b];
            e->cost = c;
            e->v1->edges[e->v1->num_edges++] = e;
            e->v2->edges[e->v2->num_edges++] = e;
        }
        find_mst(&minimum, &second_mininum);
        printf("%d %d\n", minimum, second_mininum);
    }
    return EXIT_SUCCESS;
}
