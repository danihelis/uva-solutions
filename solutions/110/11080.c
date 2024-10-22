/* 11080
 * Place the Guards
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTEX  200

typedef enum {
    BLACK,
    WHITE,
    UNKNOWN
} color_t;

typedef struct {
    int edge[MAX_VERTEX], num_edges;
    color_t color;
    int parent;
} vertex_t;

vertex_t vertex[MAX_VERTEX];
int num_vertices, minimum;

/* Add edge to sorted list of edges */
void add_edge(vertex_t *v, int e) {
    int start = 0, end = v->num_edges;
    while (start < end) {
        int middle = (start + end) / 2;
        if (v->edge[middle] == e)
            return;
        else if (v->edge[middle] > e)
            end = middle;
        else
            start = middle + 1;
    }
    for (end = v->num_edges; end > start; end--)
        v->edge[end] = v->edge[end - 1];
    v->edge[start] = e;
    v->num_edges++;
}

/* Find combination */
void find_combination(int index) {
    vertex_t *v;
    int i;
    if (index == num_vertices) {
        int blacks;
        for (i = 0, blacks = 0; i < num_vertices; i++)
            blacks += vertex[i].color == BLACK ? 1 : 0;
        if (minimum == -1 || blacks < minimum)
            minimum = blacks;
        return;
    }
    v = &vertex[index];
    if (v->color == UNKNOWN) {
        v->parent = -1;
        v->color = BLACK;
        find_combination(index);
        v->color = WHITE;
        find_combination(index);
        v->color = UNKNOWN;
    }
    else {
        int allowed, blacks;
        color_t opposite = v->color == BLACK ? WHITE : BLACK;
        for (i = 0, allowed = 1, blacks = 0; allowed && i < v->num_edges; 
                i++) {
            vertex_t *n = &vertex[v->edge[i]];
            if (n->color == v->color)
                allowed = 0;
            else if (n->color == UNKNOWN) {
                n->color = opposite;
                n->parent = index;
            }
            blacks += n->color == BLACK ? 1 : 0;
        }
        if (v->color == WHITE)
            allowed &= blacks > 0;
        if (allowed)
            find_combination(index + 1);
        for (i = 0; i < v->num_edges; i++) {
            vertex_t *n = &vertex[v->edge[i]];
            if (n->parent == index)
                n->color = UNKNOWN;
        }
    }
}


/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, edges;
        assert(scanf("%d %d", &num_vertices, &edges) != EOF);
        for (i = 0; i < num_vertices; i++)
            vertex[i].color = UNKNOWN, vertex[i].num_edges = 0;
        for (; edges > 0; edges--) {
            int v1, v2;
            assert(scanf("%d %d", &v1, &v2) != EOF);
            add_edge(&vertex[v1], v2);
            add_edge(&vertex[v2], v1);
        }
        minimum = -1;
        find_combination(0);
        printf("%d\n", minimum);
    }
    return EXIT_SUCCESS;
}
