/* 10865
 * Brownie Points
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   200000

typedef struct {
    int x, y;
} point_t;

point_t point[MAX_N];
int num_points;

/* Compute scores */
void compute_scores(int *p1, int *p2) {
    point_t center;
    int i;
    center = point[num_points / 2];
    for (i = *p1 = *p2 = 0; i < num_points; i++) {
        point_t p = point[i];
        if (p.x == center.x || p.y == center.y) continue;
        if ((p.x > center.x && p.y > center.y) ||
                (p.x < center.x && p.y < center.y)) (*p1)++;
        else (*p2)++;
    }
}

/* Main function */
int main() {
    int i, p1, p2;
    while (scanf("%d", &num_points) == 1 && num_points > 0) {
        for (i = 0; i < num_points; i++) {
            point_t *p = &point[i];
            assert(scanf("%d %d", &p->x, &p->y) == 2);
        }
        compute_scores(&p1, &p2);
        printf("%d %d\n", p1, p2);
    }
    return EXIT_SUCCESS;
}
