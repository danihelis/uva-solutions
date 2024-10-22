/* 10986
 * Sending email
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   20000
#define MAX_LINKS   50000
#define MAX_EDGES   (MAX_LINKS * 2)
#define INFINITY    (1 << 30)
#define SWAP(a, b)  do { \
        int swap = a; \
        a = b; \
        b = swap; \
    } while (0)

typedef struct {
    int source, destiny, latency;
} edge_t;

typedef struct {
    int distance, visited, queued, edge_list;
} node_t;

edge_t edges[MAX_EDGES], *p_edges[MAX_EDGES];
node_t nodes[MAX_NODES];
int num_edges, num_nodes, source, destiny;

/* Compare two edge pointers */
int compare(const void *a, const void *b) {
    edge_t *x = * (edge_t **) a, *y = * (edge_t **) b;
    return x->source - y->source;
}

/* Shortest route between source and destiny */
int shortest_distance() {
    int i, e, queue[MAX_NODES], front, rear;

    /* Sort edges and prepare edge lists; initialize nodes */
    qsort(p_edges, num_edges, sizeof (edge_t *), compare);
    for (i = 0, e = 0; i < num_nodes; i++) {
        node_t *n = &nodes[i];
        n->queued = n->visited = 0;
        n->distance = INFINITY;
        n->edge_list = e;
        for (; e < num_edges && p_edges[e]->source == i; e++)
            ;
    }

    /* BFS */
    queue[0] = source;
    nodes[source].queued = 1, nodes[source].distance = 0;
    front = 0, rear = 1;
    while (front < rear) {
        int cur = queue[front++];
        node_t *n = &nodes[cur];
        n->visited = 1;
        if (cur == destiny)
            return n->distance;
        for (e = n->edge_list; e < num_edges && p_edges[e]->source == cur;
                e++) {
            int new_dist = n->distance + p_edges[e]->latency;
            node_t *d = &nodes[p_edges[e]->destiny];
            if (!d->visited && d->distance > new_dist) {
                d->distance = new_dist;
                if (!d->queued) {
                    d->queued = 1;
                    queue[rear++] = p_edges[e]->destiny;
                }
            }
        }
        for (cur = front, i = front + 1; i < rear; i++)
            if (nodes[queue[i]].distance < nodes[queue[cur]].distance)
                cur = i;
        if (cur != front)
            SWAP(queue[cur], queue[front]);
    }
    return -1;
}


/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        int i, d;
        assert(scanf("%d %d %d %d", &num_nodes, &num_edges, &source, 
                    &destiny) != EOF);
        num_edges *= 2;
        for (i = 0; i < num_edges; i += 2) {
            edge_t *e = &edges[i];
            assert(scanf("%d %d %d", &e->source, &e->destiny, 
                        &e->latency) != EOF);
            p_edges[i] = e;
            edges[i + 1] = *e;
            p_edges[i + 1] = ++e;
            SWAP(e->source, e->destiny);
        }
        d = shortest_distance();
        printf("Case #%d: ", test + 1);
        (d == -1 ? printf("unreachable\n") : printf("%d\n", d));
    }
    return EXIT_SUCCESS;
}
