/* 10765
 * Doves and bombs
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000
#define MAX_E   15

typedef struct vertex_s {
    int edge[MAX_E], num_edges;
    int visited, low, comps;
    struct vertex_s *parent;
} vertex_t;

typedef struct {
    int index, pidgeon;
} station_t;

vertex_t vertex[MAX_N];
station_t station[MAX_N];
int num_vertices;

/* Visit and compute components in articulated points */
void visit(vertex_t *v, int *stamp) {
    int i;
    v->low = v->visited = ++(*stamp);
    for (i = 0; i < v->num_edges; i++) {
        vertex_t *n = &vertex[v->edge[i]];
        if (n->visited > 0) {
            if (v->parent != n && n->visited < v->low)
                v->low = n->visited;
        }
        else {
            n->parent = v;
            visit(n, stamp);
            v->comps += n->low >= v->visited ? 1 : 0;
            if (n->low < v->low)
                v->low = n->low;
        }
    }
    if (v->parent != NULL)
        v->comps++;
}

/* Compare two stations */
int compare(const void *a, const void *b) {
    station_t *x = (station_t *) a, *y = (station_t *) b;
    if (x->pidgeon == y->pidgeon)
        return x->index - y->index;
    return y->pidgeon - x->pidgeon;
}

/* Print best stations */
void print_stations(int k) {
    int i;
    for (i = 0; i < num_vertices; i++)
        station[i].index = i, station[i].pidgeon = vertex[i].comps;
    qsort(station, num_vertices, sizeof (station_t), compare);
    for (i = 0; i < k; i++)
        printf("%d %d\n", station[i].index, station[i].pidgeon);
    printf("\n");
}

/* Main function */
#define ADD_EDGE(a,b)   (vertex[a].edge[vertex[a].num_edges++] = b)
int main() {
    int num_stations;
    while (scanf("%d %d", &num_vertices, &num_stations) == 2 && 
            num_vertices > 0) {
        int i, j;
        for (i = 0; i < num_vertices; i++) {
            vertex_t *v = &vertex[i];
            v->visited = v->num_edges = v->comps = 0;
            v->parent = NULL;
        }
        while (scanf("%d %d", &i, &j) == 2 && i >= 0)
            ADD_EDGE(i, j), ADD_EDGE(j, i);
        i = 0;
        visit(&vertex[0], &i);
        print_stations(num_stations);
    }
    return EXIT_SUCCESS;
}
