/* 477
 * Points in Figures: Rectangles and Circles
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_FIGURES     10
#define SQ(x)           ((x) * (x))
#define LIMIT           9999.9

typedef struct {
    double x, y;
} point_t;

typedef struct {
    char rectangle;
    point_t p1, p2;
    double radius;
} figure_t;

figure_t figure[MAX_FIGURES];
int num_figures;

/* Whether figure contains the point */
int contains(figure_t *fig, point_t *p) {
    if (fig->rectangle)
        return fig->p1.x < p->x && fig->p1.y > p->y &&
                fig->p2.x > p->x && fig->p2.y < p->y;
    else
        return SQ(fig->p1.x - p->x) + SQ(fig->p1.y - p->y) < fig->radius;
}

/* Main function */
int main() {
    char type;
    point_t point;
    int i, any, count;
    num_figures = count = 0;
    while (scanf(" %c", &type) != EOF && type != '*') {
        figure_t *fig = &figure[num_figures++];
        fig->rectangle = type == 'r';
        assert(scanf("%lf %lf", &fig->p1.x, &fig->p1.y) != EOF);
        if (fig->rectangle)
            assert(scanf("%lf %lf", &fig->p2.x, &fig->p2.y) != EOF);
        else {
            assert(scanf("%lf", &fig->radius) != EOF);
            fig->radius *= fig->radius;
        }
    }
    while (scanf("%lf %lf", &point.x, &point.y) != EOF && 
            point.x < LIMIT && point.y < LIMIT) {
        count++;
        for (i = 0, any = 0; i < num_figures; i++)
            if (contains(&figure[i], &point)) {
                printf("Point %d is contained in figure %d\n", count, i + 1);
                any++;
            }
        if (!any)
            printf("Point %d is not contained in any figure\n", count);
    }
    return EXIT_SUCCESS;
}
