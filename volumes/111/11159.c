/* 11159
 * Factors and Multiples
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* NOTE: Minimum vertex cover has the same value as maximum cardinality 
 *       matching. Therefore, we solve the later. 
 */

#define MAX_N           100
#define MAX_VERTICES    (MAX_N * 2 + 2)

#define SOURCE          (MAX_VERTICES - 2)
#define SINK            (MAX_VERTICES - 1)

typedef struct {
    int value, prior;
} vertex_t;

vertex_t vertex[MAX_VERTICES];
int capacity[MAX_VERTICES][MAX_VERTICES], flow[MAX_VERTICES][MAX_VERTICES];
int size[2], total;

/* Compute maximum flow */
int compute_maximum_flow() {
    int found_sink, total_flow = 0;
    do {
        /* Find path linking source to sink */
        int queue[MAX_VERTICES], front, rear, i;
        for (i = 0; i < total; i++)
            vertex[i].prior = -1;
        vertex[SINK].prior = vertex[SOURCE].prior = -1;
        queue[0] = SOURCE, front = 0, rear = 1;
        found_sink = 0;
        while (!found_sink && front < rear) {
            int v = queue[front++];
            if (capacity[v][SINK] > flow[v][SINK])
                vertex[SINK].prior = v, found_sink = 1;
            else
                for (i = 0; i < total; i++)
                    if (vertex[i].prior == -1 &&
                            capacity[v][i] > flow[v][i])
                        queue[rear++] = i, vertex[i].prior = v;
        }

        /* Update flow network with path's capacity (which is always 1) */
        if (found_sink)
            total_flow++;
        for (i = SINK; vertex[i].prior != -1; i = vertex[i].prior) {
            flow[vertex[i].prior][i] += 1;
            flow[i][vertex[i].prior] -= 1;
        }
    } while (found_sink);
    return total_flow;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, j;

        memset(capacity, 0, sizeof (capacity));
        memset(flow, 0, sizeof (flow));

        assert(scanf("%d", &size[0]) == 1);
        for (i = 0; i < size[0]; i++) {
            vertex_t *v = &vertex[i];
            assert(scanf("%d", &v->value) == 1);
            capacity[SOURCE][i] = 1;
        }

        assert(scanf("%d", &size[1]) == 1);
        for (i = size[0], total = size[0] + size[1]; i < total; i++) {
            vertex_t *v = &vertex[i];
            assert(scanf("%d", &v->value) == 1);
            capacity[i][SINK] = 1;
            for (j = 0; j < size[0]; j++) {
                vertex_t *p = &vertex[j];
                if (v->value == 0 || 
                        (p->value != 0 && v->value % p->value == 0))
                    capacity[j][i] = 1;
            }
        }

        printf("Case %d: %d\n", test, compute_maximum_flow());
    }
    return EXIT_SUCCESS;
}
