/**
 * 125
 * Numbering Paths
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 35
#define MATRIX_SIZE (MAX_NODES * MAX_NODES)
#define INFINITY -1

int walk[MAX_NODES][MAX_NODES];
int path[MAX_NODES][MAX_NODES];
char cycle[MAX_NODES];
int nodes;


/* Generate the matrix with number of walks between two nodes */
void generate_walk_matrix() {
    int i, j, k;

    memset(cycle, 0, nodes);

    for (k = 0; k < nodes; k++) {
        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                if (walk[i][j] && (cycle[i] || cycle[j])) {
                    walk[i][j] = INFINITY;
                    continue;
                }
                else {
                    int more_walk = walk[i][k] * walk[k][j];
                    walk[i][j] += more_walk;
                    if (walk[i][j] != 0 && walk[j][i] != 0) {
                        walk[i][j] = INFINITY;
                        walk[j][i] = INFINITY;
                        cycle[i] = 1;
                        cycle[j] = 1;
                    }
                    else if (more_walk != 0 && (walk[i][k] == INFINITY || walk[k][j] == INFINITY)) {
                        walk[i][j] = INFINITY;
                    }
                }
            }
        }
    }
}


/* Main */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int main() {
    int streets, i, j;
    int map = 0;

    while (scanf("%d", &streets) == 1) {

        /* Read data */
        memset(path, 0, MATRIX_SIZE * sizeof (int));
        memset(walk, 0, MATRIX_SIZE * sizeof (int));
        nodes = 0;
        while (streets > 0) {
            scanf("%d %d", &i, &j);
            path[i][j]++;
            walk[i][j]++;
            nodes = MAX(nodes, MAX(i, j));
            streets--;
        }
        nodes++;

        /* Calculate and print result */
        generate_walk_matrix();
        printf("matrix for city %d\n", map);
        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                if (j > 0) {
                    printf(" ");
                }
                printf("%d", walk[i][j]);
            }
            printf("\n");
        }
        map++;
    }
    return 0;
}
