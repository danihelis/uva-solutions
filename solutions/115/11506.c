/* 11506
 * Angry Programmer
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_V       (50 * 2)
#define MAX_E       1000
#define INFINITY    (1 << 30)
#define OUT(v)      (num_vertices + (v))
#define MIN(x, y)   ((x) < (y) ? (x) : (y))

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int num_vertices;

/* Compute maximum network flow */
int maximum_flow() {
    int i, limit, total_flow, found_sink;
    total_flow = limit = found_sink = 0;
    do {
        /* Find path linking source to sink */
        int prior[MAX_V], queue[MAX_V], front, rear;
        for (i = 0; i < 2 * num_vertices; i++)
            prior[i] = -1;
        queue[0] = 0, front = 0, rear = 1;
        found_sink = 0;
        while (!found_sink && front < rear) {
            int cur = queue[front++];
            for (i = 1; !found_sink && i < 2 * num_vertices; i++)
                if (prior[i] == -1 && capacity[cur][i] > flow[cur][i]) {
                    queue[rear++] = i;
                    prior[i] = cur;
                    found_sink = (i == num_vertices - 1);
                }
        }
        
        /* Update flow network with path's capacity */
        total_flow += limit;
        limit = INFINITY;
        for (i = num_vertices - 1; prior[i] != -1; i = prior[i])
            limit = MIN(limit, capacity[prior[i]][i] - flow[prior[i]][i]);
        for (i = num_vertices - 1; prior[i] != -1; i = prior[i]) {
            flow[prior[i]][i] += limit;
            flow[i][prior[i]] -= limit;
        }
        assert(limit > 0);
    } while (found_sink);

    return total_flow;
}

/* Main function */
int main() {
    int num_edges;
    while (scanf("%d %d", &num_vertices, &num_edges) == 2 && 
            num_vertices > 0) {
        int i, j, v1, v2, cost;
        for (i = 0; i < 2 * num_vertices; i++)
            for (j = 0; j < 2 * num_vertices; j++)
                flow[i][j] = capacity[i][j] = 0;
        capacity[0][OUT(0)] = INFINITY;
        for (i = 0; i < num_vertices - 2; i++) {
            assert(scanf("%d %d", &v1, &cost) == 2);
            --v1;
            capacity[v1][OUT(v1)] = cost;
        }
        for (i = 0; i < num_edges; i++) {
            assert(scanf("%d %d %d", &v1, &v2, &cost) == 3);
            v1--, v2--;
            capacity[OUT(v1)][v2] = capacity[OUT(v2)][v1] = cost;
        }
        printf("%d\n", maximum_flow());
    }
    return EXIT_SUCCESS;
}
