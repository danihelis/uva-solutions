/* 11463
 * Commandos
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   100

typedef struct {
    int edge[MAX_NODES], num_edges;
    int distance[2], queued;
} vertex_t;

vertex_t vertex[MAX_NODES];
int num_vertices;

/* Compute distance between a node and every node */
void compute_distances(int start, int node_index) {
    int queue[MAX_NODES];
    int i, front, rear;

    for (i = 0; i < num_vertices; i++) {
        vertex[i].queued = i == start ? 1 : 0;
        vertex[i].distance[node_index] = 0;
    }
    queue[0] = start, front = 0, rear = 1;

    while (front < rear) {
        vertex_t *cur = &vertex[queue[front++]];
        for (i = 0; i < cur->num_edges; i++)
            if (!vertex[cur->edge[i]].queued) {
                queue[rear++] = cur->edge[i];
                vertex[cur->edge[i]].queued = 1;
                vertex[cur->edge[i]].distance[node_index] = 
                        cur->distance[node_index] + 1;
            }
    }
}

/* Find greatest distance */
int greatest_distance(int start, int end) {
    int i, maximum;
    compute_distances(start, 0);
    compute_distances(end, 1);
    for (i = 0, maximum = -1; i < num_vertices; i++) {
        int dist = vertex[i].distance[0] + vertex[i].distance[1];
        if (i == 0 || dist > maximum)
            maximum = dist;
    }
    return maximum;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, roads, start, end;
        assert(scanf("%d %d", &num_vertices, &roads) != EOF);
        for (i = 0; i < num_vertices; i++)
            vertex[i].num_edges = 0;
        for (; roads > 0; roads--) {
            assert(scanf("%d %d", &start, &end) != EOF);
            vertex[start].edge[vertex[start].num_edges++] = end;
            vertex[end].edge[vertex[end].num_edges++] = start;
        }
        assert(scanf("%d %d", &start, &end) != EOF);
        printf("Case %d: %d\n", test, greatest_distance(start, end));        
    }
    return EXIT_SUCCESS;
}
