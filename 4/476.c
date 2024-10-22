/* 476
 * Points in Figures: Rectangles
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_RECTS   10
#define LIMIT       9999.8

typedef struct {
    double top, left, bottom, right;
} rectangle_t, *rectangle_p;

rectangle_t rectangle[MAX_RECTS];
int num_rectangles;

/* Checks whether there is an rectangle intercepting a point */
int intercepts(int index, double row, double column) {
    int i, does;
    for (i = 0, does = 0; i < num_rectangles; i++) {
        rectangle_p r = &rectangle[i];
        if (column > r->left && column < r->right && row > r->bottom && row < r->top) {
            printf("Point %d is contained in figure %d\n", index + 1, i + 1);
            does = 1;
        }
    }
    return does;
}

/* Main function */
int main() {
    int i;
    double row, column;
    char info;
    num_rectangles = 0;
    while (scanf(" %c", &info) != EOF && info != '*') {
        rectangle_p r = &rectangle[num_rectangles++];
        assert(scanf("%lf %lf %lf %lf", &r->left, &r->top, &r->right, &r->bottom) != EOF);
    }
    for (i = 0; scanf("%lf %lf", &column, &row) != EOF && column < LIMIT && row < LIMIT; i++) {
        if (!intercepts(i, row, column)) {
            printf("Point %d is not contained in any figure\n", i + 1);
        }
    }
    return 0;
}
