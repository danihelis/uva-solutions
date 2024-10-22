/* 869
 * Airline Comparison
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N               26
#define INDEX(c)            ((c) - 'A')

typedef struct {
    char edge[MAX_N][MAX_N];
} graph_t;


/* Compute all paths of the graph */
void compute_all_paths(graph_t *graph) {
    int i, j, k;
    for (k = 0; k < MAX_N; k++) {
        for (i = 0; i < MAX_N; i++) {
            for (j = i + 1; j < MAX_N; j++) {
                char path = graph->edge[i][k] && graph->edge[k][j];
                graph->edge[i][j] |= path;
                graph->edge[j][i] |= path;
            }
        }
    }
}

/* Init a graph and read its edges */
void read(graph_t *graph) {
    int n;
    assert(scanf("%d", &n) != EOF);
    memset(graph->edge, 0, MAX_N * MAX_N);
    while (n-- > 0) {
        char a, b;
        assert(scanf(" %c %c", &a, &b) != EOF);
        graph->edge[INDEX(a)][INDEX(b)] = 1;
        graph->edge[INDEX(b)][INDEX(a)] = 1;
    }
    compute_all_paths(graph);
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        graph_t g1, g2;
        int i, j, equal;
        read(&g1), read(&g2);
        for (i = 0, equal = 1; equal && i < MAX_N; i++) {
            for (j = i + 1; equal && j < MAX_N; j++) {
                equal = g1.edge[i][j] == g2.edge[i][j];
            }
        }
        printf("%s\n%s", equal ? "YES" : "NO", num_tests > 0 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
