/* 10959
 * The Party, Part I
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define UNVISITED   -1

typedef struct node_s {
    struct node_s *edge[MAX_N];
    int num_edges, distance;
} node_t;

node_t node[MAX_N];
int size;

/* Visit all nodes in breadth-first order */
void visit_nodes() {
    node_t *queue[MAX_N];
    int i, front, rear;

    queue[0] = &node[0], front = 0, rear = 1;
    node[0].distance = 0;
    while (front < rear) {
        node_t *cur = queue[front++];
        for (i = 0; i < cur->num_edges; i++) {
            node_t *next = cur->edge[i];
            if (next->distance == UNVISITED) {
                next->distance = cur->distance + 1;
                queue[rear++] = next;
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int i, edges;
        assert(scanf("%d %d", &size, &edges) == 2);
        for (i = 0; i < size; i++)
            node[i].num_edges = 0, node[i].distance = UNVISITED;
        while (edges-- > 0) {
            int a, b;
            assert(scanf("%d %d", &a, &b) == 2);
            node[a].edge[node[a].num_edges++] = &node[b];
            node[b].edge[node[b].num_edges++] = &node[a];
        }
        visit_nodes();
        for (i = 1; i < size; i++)
            printf("%d\n", node[i].distance);
        if (num_tests > 0)
            puts("");
    }
    return EXIT_SUCCESS;
}
