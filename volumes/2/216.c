/* 216
 * Getting in Line
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES       8
#define DEFAULT_DIST    16.0
#define SQ(x)           ((x) * (x))

typedef struct {
    int x, y;
} point_t, *point_p;

point_t node[MAX_NODES];
int num_nodes;
double distance[MAX_NODES][MAX_NODES], best_distance;
int used[MAX_NODES], solution[MAX_NODES], best[MAX_NODES];

/* Permute all nodes to find best distance */
void permute(int order, double total) {
    if (total >= best_distance && best_distance > 0) {
        return;
    }
    else if (order >= num_nodes) {
        best_distance = total;
        memcpy(best, solution, num_nodes * sizeof (int));
    }
    else {
        int i, last;
        for (i = 0, last = num_nodes - (order == 0 ? 1 : 0); i < last; i++) {
            if (!used[i]) {
                double dist = order == 0 ? 0 : distance[solution[order - 1]][i];
                solution[order] = i, used[i] = 1;
                permute(order + 1, total + dist);
                used[i] = 0;
            }
        }
    }
}

/* Main function */
int main() {
    int network = 0;
    while (scanf("%d", &num_nodes) != EOF && num_nodes > 0) {        
        int i, j;
        double total;
        for (i = 0; i < num_nodes; i++) {
            point_p p = &node[i];
            assert(scanf("%d %d", &p->x, &p->y) != EOF);
            used[i] = 0;
        }
        for (i = 0; i < num_nodes - 1; i++) {
            for (j = i + 1; j < num_nodes; j++) {
                point_p a = &node[i], b = &node[j];
                double dist = sqrt(SQ(a->x - b->x) + SQ(a->y - b->y)) + DEFAULT_DIST;
                distance[i][j] = dist, distance[j][i] = dist;
            }
        }
        best_distance = -1;
        permute(0, 0.0);
        printf("**********************************************************\nNetwork #%d\n",
                ++network);
        for (i = 1, total = 0; i < num_nodes; i++) {
            point_p a = &node[best[i - 1]], b = &node[best[i]];
            double dist = distance[best[i - 1]][best[i]];
            total += dist;
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
                    a->x, a->y, b->x, b->y, dist);
        }
        printf("Number of feet of cable required is %.2f.\n", total);
    }
    return 0;
}
