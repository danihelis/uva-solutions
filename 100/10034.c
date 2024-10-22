/* 10034
 * Freckles
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   100
#define SQ(x)       ((x) * (x))

struct {
    double x, y;
} node[MAX_NODES];

double distance[MAX_NODES][MAX_NODES];
int num_nodes;

/* Compute a minimum spanning tree and return the total distance */
double mst() {
    char used[MAX_NODES];
    int n, connected[MAX_NODES];
    double total;

    memset(used, 0, num_nodes);
    connected[0] = 0, used[0] = 1, n = 1, total = 0;
    while (n < num_nodes) {
        int c, i, j, next;
        double minimum;
        for (i = 0, next = -1, minimum = -1; i < n; i++) {
            c = connected[i];
            for (j = 0; j < num_nodes; j++) {
                if (!used[j] && (distance[c][j] < minimum || next == -1)) {
                    next = j;
                    minimum = distance[c][j];
                }
            }
        }
        total += minimum;
        used[next] = 1;
        connected[n++] = next;
    }
    return total;
}

/* Main function */
int main() {
    int i, j, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d", &num_nodes) != EOF);
        for (i = 0; i < num_nodes; i++) {
            assert(scanf("%lf %lf", &node[i].x, &node[i].y) != EOF);
        }
        for (i = 0; i < num_nodes - 1; i++) {
            for (j = i + 1; j < num_nodes; j++) {
                double d = sqrt(SQ(node[i].x - node[j].x) + SQ(node[i].y - node[j].y));
                distance[i][j] = d, distance[j][i] = d;
            }
        }
        printf("%.2f\n%s", mst(), num_tests > 1 ? "\n" : "");
    }
    return 0;
}
