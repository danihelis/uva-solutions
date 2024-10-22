/* 478
 * Points in Figures: Rectangles, Circles, Triangles
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

typedef struct {
    double x, y;
} point_t;

typedef struct {
    point_t tl, br;
} rect_t;

typedef struct {
    point_t center;
    double radius, sq_rad;
} circle_t;

typedef struct {
    point_t a, b, c;
    int signal;
} triangle_t;

typedef struct {
    char type;
    union {
        rect_t rect;
        circle_t circle;
        triangle_t triangle;
    } shape;
} figure_t;

figure_t figure[MAX_FIGURES];
int num_figures;

/* Sine */
double sine(point_t a, point_t b, point_t c) {
    point_t ab, ac;
    ab.x = b.x - a.x, ab.y = b.y - a.y;
    ac.x = c.x - a.x, ac.y = c.y - a.y;
    return ab.x * ac.y - ac.x * ab.y;
}

/* Square distance */
double sq_dist(point_t a, point_t b) {
    return SQ(a.x - b.x) + SQ(a.y - b.y);
}

/* Signal */
int signal(double x) {
    return x < 0 ? -1 : x > 0 ? 1 : 0;
}

/* Inside rectangle */
int inside_rectangle(rect_t r, point_t p) {
    return p.x > r.tl.x && p.x < r.br.x && p.y < r.tl.y && p.y > r.br.y;
}

/* Inside circle */
int inside_circle(circle_t c, point_t p) {
    return sq_dist(c.center, p) < c.sq_rad;
}

/* Inside triangle */
int inside_triangle(triangle_t t, point_t p) {
    return signal(sine(p, t.b, t.c)) == t.signal &&
           signal(sine(t.a, p, t.c)) == t.signal &&
           signal(sine(t.a, t.b, p)) == t.signal;
}

/* Whether a point is inside the figure */
int is_inside(figure_t f, point_t p) {
    switch (f.type) {
        case 'r': return inside_rectangle(f.shape.rect, p);
        case 'c': return inside_circle(f.shape.circle, p);
        case 't': return inside_triangle(f.shape.triangle, p);
    }
    return 0;
}

/* Main function */
#define READ_POINT(p)   (scanf("%lf %lf", &(p).x, &(p).y) == 2)
int main() {
    char type;
    int count;
    point_t p;
    num_figures = 0;
    while (scanf(" %c", &type) == 1 && type != '*') {
        figure_t *f = &figure[num_figures++];
        f->type = type;
        switch (type) {
            case 'r':
                assert(READ_POINT(f->shape.rect.tl));
                assert(READ_POINT(f->shape.rect.br));
                break;
            case 'c':
                assert(READ_POINT(f->shape.circle.center));
                assert(scanf("%lf", &f->shape.circle.radius) == 1);
                f->shape.circle.sq_rad = SQ(f->shape.circle.radius);
                break;
            case 't':
                assert(READ_POINT(f->shape.triangle.a));
                assert(READ_POINT(f->shape.triangle.b));
                assert(READ_POINT(f->shape.triangle.c));
                f->shape.triangle.signal = signal(sine(
                            f->shape.triangle.a,
                            f->shape.triangle.b,
                            f->shape.triangle.c));
                break;
        }
    }
    count = 0;
    while (READ_POINT(p) && (p.x < 9999.9 || p.y < 9999.9)) {
        int i, inside;
        count++;
        for (i = inside = 0; i < num_figures; i++)
            if (is_inside(figure[i], p)) {
                inside = 1;
                printf("Point %d is contained in figure %d\n", count, i + 1);
            }
        if (!inside)
            printf("Point %d is not contained in any figure\n", count);
    }
    return EXIT_SUCCESS;
}
