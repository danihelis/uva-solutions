/* 208
 * Firetruck
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   20

typedef struct vertex_s {
    struct vertex_s *edge[MAX_N];
    int index, num_edges;
    char used;
} vertex_t;


vertex_t vertex[MAX_N];
char marked[MAX_N][MAX_N];
int path[MAX_N];

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Print all routes to destinty and return number of routes */
int find_routes(int source, int destiny, int length) {
    int i, routes = 0;
    vertex[source].used = 1;
    path[length] = source + 1;
    if (source == destiny) {
        for (i = 0; i <= length; i++) {
            printf("%d%c", path[i], i < length ? ' ' : '\n');
        }
        routes = 1;
    } else {
        for (i = 0; i < vertex[source].num_edges; i++) {
            vertex_t *v = vertex[source].edge[i];
            if (!v->used) routes += find_routes(v->index, destiny, length + 1);
        }
    }
    vertex[source].used = 0;
    return routes;
}

/* Find at least one route */
int find_any_route(int destiny) {
    int i, j, k;
    for (k = 0; k < MAX_N; k++) {
        for (i = 0; i < MAX_N; i++) {
            for (j = i + 1; j < MAX_N; j++) {
                char is_path = marked[i][k] && marked[k][j];
                marked[i][j] |= is_path, marked[j][i] |= is_path;
            }
        }
    }
    return marked[0][destiny];
}

/* Read graph */
void read_graph() {
    int i, j;
    memset(marked, 0, MAX_N * MAX_N);
    for (i = 0; i < MAX_N; i++) {
        vertex_t *v = &vertex[i];
        v->index = i, v->num_edges = 0, v->used = 0;
        marked[i][i] = 1;
    }
    while (scanf("%d %d", &i, &j) != EOF && i > 0) {
        i--, j--;
        if (marked[i][j]) continue;
        vertex[i].edge[vertex[i].num_edges++] = &vertex[j];
        vertex[j].edge[vertex[j].num_edges++] = &vertex[i];
        marked[i][j] = marked[j][i] = 1;
    }
    for (i = 0; i < MAX_N; i++) {
        vertex_t *v = &vertex[i];
        qsort(v->edge, v->num_edges, sizeof (vertex_t *), compare);
    }
}

/* Main function */
int main() {
    int test = 0, fire, routes;
    while (scanf("%d", &fire) != EOF) {
        read_graph();
        printf("CASE %d:\n", ++test);
        if (find_any_route(fire - 1)) routes = find_routes(0, fire - 1, 0);
        else routes = 0;
        printf("There are %d routes from the firestation to streetcorner %d.\n", 
                routes, fire);
    }
    return EXIT_SUCCESS;
}
