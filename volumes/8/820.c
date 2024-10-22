/* 820
 * Internet Bandwidth
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   100
#define INFINITY    (1 << 30)
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

int capacity[MAX_NODES][MAX_NODES];
int num_nodes, source, sink;

/* Find maximum flow */
int find_maximum_flow() {
    int flow[MAX_NODES][MAX_NODES];
    int i, j, total_flow;

    for (i = 0; i < num_nodes; i++) 
        for (j = 0; j < num_nodes; j++)
            flow[i][j] = 0;
    total_flow = 0;

    while (1) {
        /* Find route with maximal flowing */
        int prior[MAX_NODES], visited[MAX_NODES], flowing[MAX_NODES];
        int cur, max_flow;
        for (i = 0; i < num_nodes; i++)
            prior[i] = -1, visited[i] = 0, flowing[i] = 0;
        flowing[source] = INFINITY;
        cur = source;
        while (cur != -1) {
            visited[cur] = 1;
            if (cur == sink)
                break;
            for (i = 0; i < num_nodes; i++) {
                int potencial = MIN(flowing[cur], 
                        capacity[cur][i] - flow[cur][i]);
                if (!visited[i] && potencial > flowing[i]) {
                    prior[i] = cur;
                    flowing[i] = potencial;
                }
            }
            for (i = 0, cur = -1; i < num_nodes; i++)
                if (!visited[i] && ((cur == -1 && flowing[i] > 0) || 
                            flowing[i] > flowing[cur]))
                    cur = i;
        }

        /* Update flow */
        if (cur != sink)
            break;
        max_flow = flowing[sink];
        total_flow += max_flow;
        while (cur != source) {
            flow[prior[cur]][cur] += max_flow;
            flow[cur][prior[cur]] -= max_flow;
            cur = prior[cur];
        }
    }
    return total_flow;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_nodes) != EOF && num_nodes > 0) {
        int i, j, n;
        for (i = 0; i < num_nodes; i++)
            for (j = 0; j < num_nodes; j++)
                capacity[i][j] = 0;
        assert(scanf("%d %d %d", &source, &sink, &n) != EOF);
        source--, sink--;
        for (i = 0; i < n; i++) {
            int a, b, w;
            assert(scanf("%d %d %d", &a, &b, &w) != EOF);
            a--, b--;
            capacity[a][b] += w, capacity[b][a] += w;
        }
        printf("Network %d\nThe bandwidth is %d.\n\n", ++test, 
                find_maximum_flow());
    }
    return EXIT_SUCCESS;
}
