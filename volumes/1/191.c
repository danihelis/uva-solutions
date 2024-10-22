/*
 * 191
 * Intersection
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_SEGMENTS_RECTANGLE 4

typedef struct {
    int x, y;
} point_t, vector_t;

typedef struct {
    point_t p;
    vector_t v;
} line_t;

typedef struct {
    line_t line;
    int min_x, max_x, min_y, max_y;
} segment_t;

segment_t segment, rectangle[NUM_SEGMENTS_RECTANGLE];


/* Create segment */
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
void create_segment(segment_t *seg, point_t *a, point_t *b) {
    seg->line.p = *a;
    seg->line.v.x = (b->x - a->x);
    seg->line.v.y = (b->y - a->y);
    seg->min_x = MIN(a->x, b->x);
    seg->max_x = MAX(a->x, b->x);
    seg->min_y = MIN(a->y, b->y);
    seg->max_y = MAX(a->y, b->y);
}


/* Get intersection point between two lines */
int line_intersection(double *alpha, line_t *r, line_t *s) {
    long det = (r->v.y * s->v.x) - (r->v.x * s->v.y);
    long det_alpha = ((r->p.x - s->p.x) * s->v.y) - ((r->p.y - s->p.y) * s->v.x);

    if (det == 0) {
        return 0;
    }
    *alpha = det_alpha / ((double) (det));
    return 1;
}


/* Does the segments intercept? */
#define GREATER(d, i) (d - i > -1E-3)
#define LESSER(d, i) (i - d > -1E-3)
#define IN_INTERVAL(v, a, b) (GREATER(v, a) && LESSER(v, b))
int segment_intersection(segment_t *a, segment_t *b) {
    double alpha, ix, iy;
    if (!line_intersection(&alpha, &a->line, &b->line)) {
        return 0;
    }
    ix = a->line.p.x + a->line.v.x * alpha;
    iy = a->line.p.y + a->line.v.y * alpha;
    return (IN_INTERVAL(ix, a->min_x, a->max_x) && IN_INTERVAL(iy, a->min_y, a->max_y) &&
            IN_INTERVAL(ix, b->min_x, b->max_x) && IN_INTERVAL(iy, b->min_y, b->max_y));
}


/* Create rectangle segments */
#define SET_POINT(p, xv, yv) (p).x = xv; (p).y = yv
#define SET_SEGMENT(s, xs, xe, ys, ye) \
    do { \
        point_t p1, p2; \
        SET_POINT(p1, xs, ys); \
        SET_POINT(p2, xe, ye); \
        create_segment(&s, &p1, &p2); \
    } while (0)
void create_rectangle_segments(point_t *lt, point_t *rb) {
    SET_SEGMENT(rectangle[0], lt->x, rb->x, lt->y, lt->y);
    SET_SEGMENT(rectangle[1], rb->x, rb->x, lt->y, rb->y);
    SET_SEGMENT(rectangle[2], lt->x, lt->x, rb->y, lt->y);
    SET_SEGMENT(rectangle[3], rb->x, lt->x, rb->y, rb->y);
}


/* Main function */
int main() {
    int num_data_set, data_set;
    point_t start, end, rect_tl, rect_rb;

    assert(scanf("%d", &num_data_set) != EOF);
    for (data_set = 0; data_set < num_data_set; data_set++) {
        int i, intersection;

        assert(scanf("%d %d", &start.x, &start.y) != EOF);
        assert(scanf("%d %d", &end.x, &end.y) != EOF);
        assert(scanf("%d %d", &rect_tl.x, &rect_tl.y) != EOF);
        assert(scanf("%d %d", &rect_rb.x, &rect_rb.y) != EOF);

        /* Dubious code, I don't know if I need it... */
        {
            if (rect_tl.x > rect_rb.x) {
                int t = rect_tl.x;
                rect_tl.x = rect_rb.x;
                rect_rb.x = t;
            }
            if (rect_tl.y < rect_rb.y) {
                int t = rect_tl.y;
                rect_tl.y = rect_rb.y;
                rect_rb.y = t;

            }
        }

        /* If it is inside, than there's an intersection */
        if (IN_INTERVAL(start.x, rect_tl.x, rect_rb.x) && IN_INTERVAL(end.x, rect_tl.x, rect_rb.x) &&
                IN_INTERVAL(start.y, rect_rb.y, rect_tl.y) && IN_INTERVAL(end.y, rect_rb.y, rect_tl.y)) {
            printf("T\n");
            continue;
        }

        /* Check segments intersection */
        create_segment(&segment, &start, &end);
        create_rectangle_segments(&rect_tl, &rect_rb);
        for (i = 0, intersection = 0; !intersection && i < NUM_SEGMENTS_RECTANGLE; i++) {
            intersection = segment_intersection(&segment, &rectangle[i]);
        }
        printf("%c\n", (intersection ? 'T' : 'F'));
    }
    
    return 0;
}
