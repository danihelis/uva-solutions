/* 11015
 * 05-2 Rendezvous
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           22
#define MAX_STRING      12
#define INFINITY        (1 << 29)
#define DIST(i,j)       ((i) < (j) ? distance[i][j] : distance[j][i])

char name[MAX_N][MAX_STRING];
int distance[MAX_N][MAX_N], size;

/* Compute minimal distances */
void compute_minimal_distances() {
    int i, j, k;
    for (k = 0; k < size; k++)
        for (i = 0; i < size; i++)
            for (j = i + 1; j < size; j++)
                if (k != i && k != j) {
                    int new = DIST(i, k) + DIST(k, j);
                    if (new < distance[i][j])
                        distance[i][j] = new;
                }
}

/* Find node which minimizes all distances to it */
int find_best_node() {
    int i, j, cost[MAX_N], best;
    compute_minimal_distances();

    memset(cost, 0, sizeof (cost));
    for (i = 0; i < size; i++)
        for (j = i + 1; j < size; j++)
            cost[i] += distance[i][j], cost[j] += distance[i][j];

    for (best = 0, i = 1; i < size; i++)
        if (cost[i] < cost[best])
            best = i;
    return best;
}

/* Main function */
int main() {
    int edges, test = 0;
    while (scanf("%d %d", &size, &edges) == 2 && size > 0) {
        int i, j, k;
        for (i = 0; i < size; i++) {
            assert(scanf(" %s", name[i]) == 1);
            for (j = i + 1; j < size; j++)
                distance[i][j] = INFINITY;
        }
        for (; edges > 0; edges--) {
            assert(scanf("%d %d %d", &i, &j, &k) == 3);
            --i, --j;
            distance[i][j] = distance[j][i] = k;
        }
        k = find_best_node();
        printf("Case #%d : %s\n", ++test, name[k]);
    }
    return EXIT_SUCCESS;
}
