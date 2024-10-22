/* 10167
 * Birthday Cake
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       500
#define MAX_COORDS  400000
#define MAX_POINTS  100

typedef struct {
    int a, b;
} coord_t;

typedef struct {
    int x, y;
} point_t;

coord_t coord[MAX_COORDS];
point_t point[MAX_POINTS];
int num_coords, num_points;

/* Generate all possible coordinates */
void generate_coordinates() {
    char composite[MAX_N][MAX_N];
    int i, j, p, q;
    memset(composite, 0, MAX_N * MAX_N);
    coord[0].a = 0, coord[0].b = 1;
    coord[1].a = 1, coord[1].b = 0;
    num_coords = 2;
    for (i = 1; i <= MAX_N; i++) {
        for (j = i; j <= MAX_N; j++) {
            if (composite[i - 1][j - 1]) continue;
            coord[num_coords].a = i, coord[num_coords].b = j;
            coord[num_coords + 1].a = i, coord[num_coords + 1].b = -j;
            num_coords += 2;
            if (i != j) {
                coord[num_coords].a = j, coord[num_coords].b = i;
                coord[num_coords + 1].a = j, coord[num_coords + 1].b = -i;
                num_coords += 2;
            }
            for (p = 2 * i, q = 2 * j; p <= MAX_N && q <= MAX_N; p += i, q += j) {
                composite[p - 1][q - 1] = 1;
            }
        }
    }
    /* Randomize vector, because it improves search performance! :) */
    for (i = 0; i < num_coords / 2; i++) {
        coord_t c;
        j = rand() % num_coords;
        c = coord[i];
        coord[i] = coord[j];
        coord[j] = c;
    }
}

/* Find coordinate that divides all points in two */
coord_t *find_coordinate() {
    int i, j, n, u, v, k;
    for (i = 0, n = num_points / 2; i < num_coords; i++) {
        coord_t *c = &coord[i];
        for (j = u = v = 0; j < num_points && u <= n && v <= n; j++) {
            point_t *p = &point[j];
            k = p->x * c->a + p->y * c->b;
            if (k == 0) break;
            if (k > 0) u++;
            else v++;
        }
        if (u == n && v == n) return c;
    }
    return NULL;
}

/* Main function */
int main() {
    generate_coordinates();
    while (scanf("%d", &num_points) == 1 && num_points > 0) {
        int i;
        coord_t *c;
        num_points *= 2;
        for (i = 0; i < num_points; i++) {
            point_t *p = &point[i];
            assert(scanf("%d %d", &p->x, &p->y) == 2);
        }
        c = find_coordinate();
        assert(c != NULL);
        printf("%d %d\n", c->a, c->b);
    }
    return EXIT_SUCCESS;
}
