/* 10264
 * The Most Potent Corner
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CORNERS  32800

typedef struct {
    int weight, power;
} corner_t;

corner_t corner[MAX_CORNERS];
int dimensions, num_corners;

/* Compute corner's power */
void compute_power() {
    int i, k;
    for (i = 0; i < num_corners; i++) {
        corner[i].power = 0;
        for (k = 0; k < dimensions; k++) {
            int neigh = (i & (1 << k)) ? (i & ~(1 << k)) : (i | (1 << k));
            corner[i].power += corner[neigh].weight;
        }
    }
}

/* Determines edge with highest sum of corners' powers */
int get_highest_edge() {
    int i, k, highest;
    for (i = 0, highest = 0; i < num_corners; i++) {
        for (k = 0; k < dimensions; k++) {
            int neigh = (i & (1 << k)) ? (i & ~(1 << k)) : (i | (1 << k));
            int total = corner[i].power + corner[neigh].power;
            if (total > highest) {
                highest = total;
            }
        }
    }
    return highest;
}

/* Main function */
int main() {
    while (scanf("%d", &dimensions) != EOF) {
        int i;
        num_corners = 1 << dimensions;
        for (i = 0; i < num_corners; i++) {
            assert(scanf("%d", &corner[i].weight) != EOF);
        }
        compute_power();
        printf("%d\n", get_highest_edge());
    }
    return 0;
}
