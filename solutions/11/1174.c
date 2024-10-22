/* 1174
 * IP-TV
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      10
#define MAX_VERTICES    2000
#define MAX_EDGES       50000

typedef void * set_t;

typedef struct {
    char name[MAX_STRING];
    set_t set;
} vertex_t;

typedef struct {
    vertex_t *a, *b;
    short cost;
} edge_t;

vertex_t vertex[MAX_VERTICES], *p_vertex[MAX_VERTICES];
edge_t edge[MAX_EDGES];
int num_vertices, num_edges;

/* Compare two edges */
int compare_edge(const void *a, const void *b) {
    return ((edge_t *) a)->cost - ((edge_t *) b)->cost;
}

/* Find or insert vertex */
vertex_t * get_vertex(char *name) {
    int start = 0, end = num_vertices;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(name, p_vertex[middle]->name);
        if (cmp == 0)
            return p_vertex[middle];
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    strcpy(vertex[num_vertices].name, name);
    vertex[num_vertices].set = &vertex[num_vertices].set;
    for (end = num_vertices; end > start; end--)
        p_vertex[end] = p_vertex[end - 1];
    p_vertex[start] = &vertex[num_vertices++];
    return p_vertex[start];
}

/* Get set */
set_t get_set(set_t *s) {
    if (*s != s)
        *s = get_set(*s);
    return *s;
}

/* Join sets */
void join_sets(set_t *a, set_t *b) {
    set_t *head = get_set(a);
    *head = get_set(b);
}

/* Minimum spanning tree */
int mst() {
    int i, k, cost;
    qsort(edge, num_edges, sizeof (edge_t), compare_edge);
    for (i = k = cost = 0; i < num_edges && k < num_vertices - 1; i++) {
        vertex_t *a = edge[i].a, *b = edge[i].b;
        if (get_set(&a->set) != get_set(&b->set)) {
            join_sets(&a->set, &b->set);
            cost += edge[i].cost, k++;
        }
    }
    assert(k == num_vertices - 1);
    return cost;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, n;
        assert(scanf("%d %d", &n, &num_edges) == 2);
        for (num_vertices = 0, i = 0; i < num_edges; i++) {
            char name[2][MAX_STRING];
            short cost;
            assert(scanf(" %s %s %hd", name[0], name[1], &cost) == 3);
            edge[i].a = get_vertex(name[0]);
            edge[i].b = get_vertex(name[1]);
            edge[i].cost = cost;
        }
        assert(num_vertices == n);
        printf("%d\n%s", mst(), num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
