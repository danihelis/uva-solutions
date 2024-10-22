/* 11770
 * Lighting Away
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    10000

typedef struct vertex_s {
    struct vertex_s *edge[MAX_VERTICES];
    int lighted, listed, num_edges;
} vertex_t;

vertex_t vertex[MAX_VERTICES], *list[MAX_VERTICES];
int num_vertices, list_size;


/* Reverse traversal for topological sort */
void reverse_dfs(vertex_t *v) {
    int i;
    v->listed = 1;
    for (i = 0; i < v->num_edges; i++) {
        vertex_t *n = v->edge[i];
        if (!n->listed) reverse_dfs(n);
    }
    list[list_size++] = v;
}

/* Topological sort */
void topological_sort() {
    int i;
    for (i = list_size = 0; i < num_vertices; i++) {
        vertex_t *v = &vertex[i];
        if (!v->listed) reverse_dfs(v);
    }
    assert(list_size == num_vertices);
}

/* Depth-first search for lights */
void dfs(vertex_t *v) {
    int i;
    v->lighted = 1;
    for (i = 0; i < v->num_edges; i++) {
        vertex_t *n = v->edge[i];
        if (!n->lighted) dfs(n);
    }
}

/* Compute how many lights must be switched */
int count_switch() {
    int i, swicthes;
    topological_sort();
    for (i = list_size, swicthes = 0; i > 0; i--) {
        vertex_t *v = list[i - 1];
        if (!v->lighted) {
            dfs(v);
            swicthes++;
        }
    }
    return swicthes;
}

/* Read graph */
void read_graph() {
    int i, num_edges, a, b;
    assert(scanf("%d %d", &num_vertices, &num_edges) == 2);
    for (i = 0; i < num_vertices; i++) {
        vertex_t *v = &vertex[i];
        v->lighted = v->listed = v->num_edges = 0;
    }
    while (num_edges-- > 0) {
        vertex_t *v;
        assert(scanf("%d %d", &a, &b) == 2);
        v = &vertex[--a];
        v->edge[v->num_edges++] = &vertex[--b];
    }
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        read_graph();
        printf("Case %d: %d\n", test, count_switch());
    }
    return EXIT_SUCCESS;
}
