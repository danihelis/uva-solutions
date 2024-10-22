/* 988
 * Many Paths, One Destination
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000

typedef struct {
    int edge[MAX_N], num_edges;
    int choices;
} node_t;

/* Main function */
int main() {
    node_t node[MAX_N];
    int n, first = 1;
    while (scanf("%d", &n) != EOF) {
        int i, j;
        for (i = 0; i < n; i++) {
            node_t *n = &node[i];
            assert(scanf("%d", &n->num_edges) == 1);
            for (j = 0; j < n->num_edges; j++)
                assert(scanf("%d", &n->edge[j]) == 1);
        }
        for (i = n - 1; i >= 0; i--) {
            node_t *n = &node[i];
            for (j = n->choices = 0; j < n->num_edges; j++)
                n->choices += node[n->edge[j]].choices;
            if (n->choices == 0)
                n->choices = 1;
        }
        (first ? (first = 0) : printf("\n"));
        printf("%d\n", node[0].choices);
    }
    return EXIT_SUCCESS;
}
