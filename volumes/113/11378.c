/* 11378
 * Bey Battle
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100000
#define INFINITY    10000000

typedef struct {
    int x, y;
} point_t;

point_t point[MAX_DIM];

/* Compare two points */
int compare(const void *a, const void *b) {
    point_t *pa = (point_t *) a, *pb = (point_t *) b;
    if (pa->x == pb->x)
        return pa->y - pb->y;
    return pa->x - pb->x;
}

/* Maximum distance */ 
int max_dist(int i, int j) {
    int dx = abs(point[i].x - point[j].x), 
        dy = abs(point[i].y - point[j].y);
    return dx > dy ? dx : dy;
}

/* Return the closest maximal distance */
int close_distance(int start, int end) {
    int i, j, k, m, b1, b2, best;
    if (end - start <= 3) {
        for (i = start, best = INFINITY; i < end - 1; i++)
            for (j = i + 1; j < end; j++) {
                m = max_dist(i, j);
                if (m < best)
                    best = m;
            }
        return best;
    }
    k = (start + end) / 2;
    b1 = close_distance(start, k), b2 = close_distance(k, end);
    best = b1 < b2 ? b1 : b2;
    for (i = start > k - 4 ? start : k - 4; i < k; i++)
        for (j = k, m = end < k + 4 ? end : k + 4; j < m; j++) {
            b1 = max_dist(i, j);
            if (b1 < best)
                best = b1;
        }
    return best;
}

/* Main function */
int main() {
    int n, i;
    while (scanf("%d", &n) != EOF) {
        for (i = 0; i < n; i++)
            assert(scanf("%d %d", &point[i].x, &point[i].y) != EOF);
        qsort(point, n, sizeof (point_t), compare);
        printf("%d\n", close_distance(0, n));
    }
    return EXIT_SUCCESS;
}
