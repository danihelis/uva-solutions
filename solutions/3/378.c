/* 378
 * Intersecting Lines
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    int x, y;
} point_t;

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    printf("INTERSECTING LINES OUTPUT\n");
    for (; num_tests > 0; num_tests--) {
        point_t p[4], d[2], delta;
        int i, det, scalar;
        for (i = 0; i < 4; i++)
            assert(scanf("%d %d", &p[i].x, &p[i].y) == 2);
        for (i = 0; i < 2; i++)
            d[i].x = p[2 * i + 1].x - p[2 * i].x,
            d[i].y = p[2 * i + 1].y - p[2 * i].y;
        det = d[0].x * d[1].y - d[1].x * d[0].y;
        delta.x = p[2].x - p[0].x, delta.y = p[2].y - p[0].y;
        scalar = delta.x * d[1].y - delta.y * d[1].x;
        if (det == 0)
            printf("%s\n", scalar == 0 ? "LINE" : "NONE");
        else {
            double x = p[0].x + (double) d[0].x * scalar / det,
                   y = p[0].y + (double) d[0].y * scalar / det;
            printf("POINT %.2f %.2f\n", x, y);
        }
    }
    printf("END OF OUTPUT\n");
    return EXIT_SUCCESS;
}
