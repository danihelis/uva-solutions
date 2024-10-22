/* 1112
 * Mice and Maze
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CELLS   100

int distance[MAX_CELLS][MAX_CELLS];
int num_cells;

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j, k, time, exit, edges, count;
        assert(scanf("%d %d %d %d", &num_cells, &exit, &time, 
                &edges) != EOF);
        for (i = 0; i < num_cells; i++)
            for (j = 0; j < num_cells; j++)
                distance[i][j] = i == j ? 0 : time + 1;
        for (; edges > 0; edges--) {
            int c1, c2, cost;
            assert(scanf("%d %d %d", &c1, &c2, &cost) != EOF);
            c1--, c2--;
            if (distance[c1][c2] > cost)
                distance[c1][c2] = cost;
        }
        for (k = 0; k < num_cells; k++) 
            for (i = 0; i < num_cells; i++)
                for (j = 0; j < num_cells; j++) {
                    int cost = distance[i][k] + distance[k][j];
                    if (distance[i][j] > cost)
                        distance[i][j] = cost;
                }
        for (i = 0, count = 0, --exit; i < num_cells; i++)
            count += distance[i][exit] <= time ? 1 : 0;
        printf("%d%s\n", count, num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
