/* 280
 * Vertex
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    100
#define MAX_SIZE        (MAX_VERTICES * MAX_VERTICES)

char connect[MAX_VERTICES][MAX_VERTICES];
int num_vertices, num_unconnected[MAX_VERTICES];

/* Determine the connections between all vertices (Floyd-Warshall) */
void determine_connections() {
    int a, b, k;
    for (k = 0; k < num_vertices; k++) {
        for (a = 0; a < num_vertices; a++) {
            if (connect[a][k]) {
                for (b = 0; b < num_vertices; b++) {
                    connect[a][b] |= connect[k][b];
                }
            }
        }
    }
    for (a = 0; a < num_vertices; a++) {
        for (num_unconnected[a] = 0, b = 0; b < num_vertices; b++) {
            num_unconnected[a] += connect[a][b] ? 0 : 1;
        }
    }
}

/* Main function */
int main() {
    while (scanf("%d", &num_vertices) != EOF && num_vertices > 0) {
        int a, b, n;
        memset(connect, 0, MAX_SIZE);
        while (scanf("%d", &a) != EOF && a > 0) {
            a--;
            while (scanf("%d", &b) != EOF && b > 0) {
                connect[a][--b] = 1;
            }
        }
        determine_connections();
        assert(scanf("%d", &n) != EOF);
        for (; n > 0; n--) {
            assert(scanf("%d", &a) != EOF);
            printf("%d", num_unconnected[--a]);
            for (b = 0; b < num_vertices; b++) {
                if (!connect[a][b]) {
                    printf(" %d", b + 1);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
