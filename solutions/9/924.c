/* 924
 * Spreading The News
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    2500
#define MAX_EDGES       15

typedef struct vertex_s {
    struct vertex_s *edges[MAX_EDGES];
    int num_edges, distance;
} vertex_t;

vertex_t vertices[MAX_VERTICES];
int num_vertices;

/* Compute maximum distance between source and vertices */
void compute_distances(int source, int *boom, int *day) {
    vertex_t *queue[MAX_VERTICES];
    int boom_count[MAX_VERTICES];
    int i, rear, front, max_dist;

    for (i = 0; i < num_vertices; i++)
        vertices[i].distance = -1, boom_count[i] = 0;

    vertices[source].distance = 0;
    queue[0] = &vertices[source];
    rear = 1, front = 0;
    while (front < rear) {
        vertex_t *v = queue[front++];
        for (i = 0; i < v->num_edges; i++) {
            vertex_t *n = v->edges[i];
            if (n->distance < 0) {
                n->distance = v->distance + 1;
                queue[rear++] = n;
            }
        }
    }

    for (i = max_dist = 0; i < num_vertices; i++) {
        vertex_t *v = &vertices[i];
        if (v->distance > 0) {
            boom_count[v->distance]++;
            if (v->distance > max_dist)
                max_dist = v->distance;
        }
    }
    
    for (i = 1, *boom = *day = 0; i <= max_dist; i++)
        if (boom_count[i] > *boom)
            *boom = boom_count[i], *day = i;
}

/* Main function */
int main() {
    int i, n, e, num_tests;

    assert(scanf("%d", &num_vertices) != EOF);
    for (i = 0; i < num_vertices; i++) {
        vertex_t *v = &vertices[i];
        assert(scanf("%d", &v->num_edges) != EOF);
        for (e = 0; e < v->num_edges; e++) {
            assert(scanf("%d", &n) != EOF);
            v->edges[e] = &vertices[n];
        }
    }

    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int source, boom, day;
        assert(scanf("%d", &source) != EOF);
        compute_distances(source, &boom, &day);
        if (boom == 0)
            printf("0\n");
        else
            printf("%d %d\n", boom, day);
    }
    return EXIT_SUCCESS;
}
