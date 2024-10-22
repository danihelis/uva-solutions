/* 11902
 * Dominator
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           100

typedef struct vertex_s {
    struct vertex_s *edge[MAX_N];
    char dominate[MAX_N];
    int index, num_edges, visited, reachable;
} vertex_t;

vertex_t vertex[MAX_N];
int num_vertices;

/* Visit all nodes but the excluded one */
void visit(vertex_t *v, int excluded) {
    int i;
    v->visited = 1;
    for (i = 0; i < v->num_edges; i++) {
        vertex_t *n = v->edge[i];
        if (!n->visited && n->index != excluded)
            visit(n, excluded);
    }
}

/* Compute dominance */
void compute_dominance() {
    int e, i;
    for (i = 0; i < num_vertices; i++) {
        vertex[i].visited = vertex[i].reachable = 0;
        memset(vertex[i].dominate, 0, num_vertices);
    }
    visit(&vertex[0], -1);
    for (i = 0; i < num_vertices; i++) {
        if (vertex[i].visited)
            vertex[i].reachable = 1, vertex[0].dominate[i] = 1;
        vertex[i].visited = 0;
    }
    for (e = 1; e < num_vertices; e++)
        if (vertex[e].reachable) {
            visit(&vertex[0], e);
            for (i = 0; i < num_vertices; i++) {
                if (!vertex[i].visited && vertex[i].reachable)
                    vertex[e].dominate[i] = 1;
                vertex[i].visited = 0;
            }
        }
}

/* Print dominance table */
#define PRINT_LINE()  do { \
        int k; \
        putchar('+'); \
        for (k = 0; k < num_vertices * 2 - 1; k++) \
            putchar('-'); \
        puts("+"); \
    } while (0)

void print_dominance() {
    int i, j;
    for (i = 0; i < num_vertices; i++) {
        PRINT_LINE();
        for (j = 0; j < num_vertices; j++)
            printf("|%c", vertex[i].dominate[j] ? 'Y' : 'N');
        puts("|");
    }
    PRINT_LINE();
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, j, has_edge;
        assert(scanf("%d", &num_vertices) == 1);
        for (i = 0; i < num_vertices; i++) {
            vertex_t *v = &vertex[i];
            v->num_edges = 0, v->index = i;
            for (j = 0; j < num_vertices; j++) {
                assert(scanf("%d", &has_edge) == 1);
                if (has_edge && i != j)
                    v->edge[v->num_edges++] = &vertex[j];
            }
        }
        compute_dominance();
        printf("Case %d:\n", test);
        print_dominance();
    }
    return EXIT_SUCCESS;
}
