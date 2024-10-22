/* 10048
 * Audiophobia
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   100
#define MAX_EDGES   1000

#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MAX3(x,y,z) (MAX(x, MAX(y, z)))

typedef struct {
    int a, b, noise;
} edge_t;

edge_t edges[MAX_EDGES];
int nodeset[MAX_NODES];
int num_edges, num_nodes, noise[MAX_NODES][MAX_NODES];

/* Compare two edges */
int compare(const void *a, const void *b) {
    return ((edge_t *) a)->noise - ((edge_t *) b)->noise;
}

/* Get set */
int get_set(int n) {
    if (nodeset[n] == n)
        return n;
    nodeset[n] = get_set(nodeset[n]);
    return nodeset[n];
}

/* Minimum spanning tree */
void mst() {
    int i, total;
    qsort(edges, num_edges, sizeof (edge_t), compare);
    for (i = 0; i < num_nodes; i++) {
        nodeset[i] = i;
        memset(noise[i], 0xff, num_nodes * sizeof (int));
        noise[i][i] = 0;
    }

    for (i = 0, total = 0; i < num_edges && total < num_nodes - 1; i++) {
        edge_t *e = &edges[i];
        int set_a = get_set(e->a), set_b = get_set(e->b);
        if (set_a != set_b) {
            int elem_a[MAX_NODES], elem_b[MAX_NODES], size_a, size_b, i, j;
            for (i = size_a = size_b = 0; i < num_nodes; i++) {
                int set = get_set(nodeset[i]);
                if (set == set_a)
                    elem_a[size_a++] = i;
                if (set == set_b)
                    elem_b[size_b++] = i;
            }
            nodeset[set_a] = set_b;
            total++;
            for (i = 0; i < size_a; i++)
                for (j = 0; j < size_b; j++)
                    noise[elem_a[i]][elem_b[j]] = 
                            noise[elem_b[j]][elem_a[i]] = 
                                    MAX3(noise[elem_a[i]][e->a], e->noise, 
                                    noise[elem_b[j]][e->b]);
        }
    }
}

/* Main function */
int main() {
    int test = 0, num_queries;
    while (scanf("%d %d %d", &num_nodes, &num_edges, &num_queries) != EOF &&
            num_nodes > 0) {
        int i, a, b;
        for (i = 0; i < num_edges; i++) {
            edge_t *e = &edges[i];
            assert(scanf("%d %d %d", &e->a, &e->b, &e->noise) != EOF);
            e->a--, e->b--;
        }
        mst();
        if (test > 0)
            printf("\n");
        printf("Case #%d\n", ++test);
        for (i = 0; i < num_queries; i++) {
            assert(scanf("%d %d", &a, &b) != EOF);
            a--, b--;
            if (noise[a][b] < 0) 
                printf("no path\n");
            else
                printf("%d\n", noise[a][b]);
        }
    }
    return EXIT_SUCCESS;
}
