/* 341
 * Non-Stop Travel
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       12
#define INFINITY    (1 << 30)

typedef struct node_s {
    struct node_s *edge[MAX_N], *parent;
    int cost[MAX_N], num_edges, distance, enqueued;
} node_t;

node_t node[MAX_N], *path[MAX_N];
int num_nodes, path_size;

/* Find shortest path between two nodes */
int find_shortest_path(node_t *start, node_t *end) {
    node_t *queue[MAX_N];
    int i, min, front, rear;
    for (i = 0; i < num_nodes; i++)
        node[i].distance = INFINITY, node[i].parent = NULL, node[i].enqueued = 0;
    
    start->distance = 0, start->enqueued = 1;
    queue[0] = start, front = 0, rear = 1;
    while (front < rear) {
        node_t *cur = queue[front++];
        if (cur == end) {
            for (path_size = 0; cur != NULL; cur = cur->parent, path_size++)
                path[path_size] = cur;
            return end->distance;
        }
        for (i = 0; i < cur->num_edges; i++) {
            node_t *next = cur->edge[i];
            int dist = cur->distance + cur->cost[i];
            if (dist < next->distance) {
                next->distance = dist;
                next->parent = cur;
                if (!next->enqueued)
                    queue[rear++] = next, next->enqueued = 1;
            }
        }
        for (min = front, i = front + 1; i < rear; i++)
            if (queue[i]->distance < queue[min]->distance)
                min = i;
        if (min != front) {
            node_t *swap = queue[min];
            queue[min] = queue[front];
            queue[front] = swap;
        }
    }
    path_size = 0;
    return INFINITY;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_nodes) == 1 && num_nodes > 0) {
        int i, j, k, cost;
        for (i = 0; i < num_nodes; i++) {
            node_t *n = &node[i];
            assert(scanf("%d", &n->num_edges) == 1);
            for (j = 0; j < n->num_edges; j++) {
                assert(scanf("%d %d", &k, &n->cost[j]) == 2);
                n->edge[j] = &node[--k];
            }
        }
        assert(scanf("%d %d", &i, &j) == 2);
        cost = find_shortest_path(&node[--i], &node[--j]);
        printf("Case %d: Path =", ++test);
        for (i = path_size - 1; i >= 0; i--)
            printf(" %d", (int) (path[i] - node) + 1);
        printf("; %d second delay\n", cost);
    }
    return EXIT_SUCCESS;
}
