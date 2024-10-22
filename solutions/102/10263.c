/* 10263
 * Railway
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ZERO(n) (fabs(n) < 1e-4)

typedef struct {
    double x, y;
} vector_t;

/* Difference */
vector_t diff(vector_t a, vector_t b) {
    vector_t r;
    r.x = a.x - b.x, r.y = a.y - b.y;
    return r;
}

/* Norm */
double norm(vector_t p) {
    return p.x * p.x + p.y * p.y;
}

/* Orthogonal */
vector_t ortho(vector_t v) {
    vector_t r = {0, 1};
    if (!ZERO(v.y))
        r.x = 1, r.y = 0 - v.x / v.y;
    return r;
}

/* Sine of two vectors */
double vsin(vector_t a, vector_t b) {
    return a.x * b.y - a.y * b.x;
}

/* Segment closest distance */
double segment_closest_point(vector_t *r, vector_t a, vector_t b, 
        vector_t p) {
    vector_t dir = diff(b, a);
    vector_t o = ortho(dir);
    double k = vsin(diff(p, a), o) / vsin(dir, o);
    if (k > 0 && k < 1) {
        r->x = a.x + dir.x * k, r->y = a.y + dir.y * k;
        return norm(diff(*r, p));
    }
    else {
        double da = norm(diff(p, a)), db = norm(diff(p, b));
        *r = db < da ? b : a;
        return db < da ? db : da;
    }
}

/* Main function */
#define READ(v)     (scanf("%lf %lf", &(v).x, &(v).y) == 2)
int main() {
    vector_t m;
    while (READ(m)) {
        int n;
        double dist, closest;
        vector_t p = {0, 0}, a, b, r;
        assert(scanf("%d", &n) == 1 && READ(b));
        for (closest = HUGE_VAL; n > 0; n--) {
            a = b;
            assert(READ(b));
            dist = segment_closest_point(&r, a, b, m);
            if (dist < closest)
                closest = dist, p = r;
        }
        printf("%.4f\n%.4f\n", p.x, p.y);
    }
    return EXIT_SUCCESS;
}
