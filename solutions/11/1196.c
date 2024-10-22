/* 1196
 * Tiling Up Blocks
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

typedef struct {
    int x, y;
} tile_t;

tile_t tile[MAX_N];
int num_tiles;

/* Compare two tiles */
int compare(const void *a, const void *b) {
    tile_t *pa = (tile_t *) a, *pb = (tile_t *) b;
    return pa->x == pb->x ? pa->y - pb->y : pa->x - pb->x;
}

/* Find maximum stacking tiles */
int get_maximum() {
    tile_t *lowest[MAX_N];
    int i, j, n;
    qsort(tile, num_tiles, sizeof (tile_t), compare);
    for (i = n = 0; i < num_tiles; i++) {
        tile_t *t = &tile[i];
        for (j = n; j > 0 && t->y < lowest[j - 1]->y; j--)
            ;
        lowest[j] = t;
        if (j == n) n++;
    }
    return n;
}

/* Main function */
int main() {
    while (scanf("%d", &num_tiles) == 1 && num_tiles > 0) {
        int i;
        for (i = 0; i < num_tiles; i++) {
            tile_t *t = &tile[i];
            assert(scanf("%d %d", &t->x, &t->y) == 2);
        }
        printf("%d\n", get_maximum());
    }
    printf("*\n");
    return EXIT_SUCCESS;
}
