/* 756
 * Biorhythms
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CYCLE_P     23
#define CYCLE_E     28
#define CYCLE_I     33

#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

#define SWAP(v1, v2, exp) do { \
    int swap = exp; v1 = v2; v2 = swap; \
} while (0)

typedef struct {
    int offset, peak;
} cycle_t;

/* Solve the diophantine equation a·x - b·y = 1 for a, b co-primes */
void diophantine(int a, int b, int *x, int *y) {
    int x0 = 1, x1 = 0, y0 = 0, y1 = 1;
    while (b > 0) {
        int q = a / b;
        SWAP(x0, x1, x0 - x1 * q);
        SWAP(y0, y1, y0 - y1 * q);
        SWAP(a, b, a % b);
    }
    *x = x0, *y = -y0;
}

/* Compute peak from two cycles */
void compute_peak(cycle_t *a, cycle_t *b, cycle_t *res) {
    int lcm = a->peak * b->peak, diff = b->offset - a->offset;
    int ra, rb, k = 0;
    res->peak = lcm;
    diophantine(a->peak, b->peak, &ra, &rb);
    ra *= diff, rb *= diff;
    if (ra < 0) {
        k = 1 - MAX(ra / b->peak, rb / a->peak);
        ra += k * b->peak, rb += k * a->peak;
    }
    k = 0 - MIN(ra / b->peak, rb / a->peak);
    ra += b->peak * k, rb += a->peak * k;
    assert(ra * a->peak + a->offset == rb * b->peak + b->offset);
    res->offset = ra * a->peak + a->offset;
}

/* Main function */
int main() {
    int day, test = 0;
    cycle_t p, e, i, partial, final;
    p.peak = CYCLE_P, e.peak = CYCLE_E, i.peak = CYCLE_I;
    while (scanf("%d %d %d %d", &p.offset, &e.offset, &i.offset, &day) != EOF 
            && day >= 0) {
        p.offset %= p.peak, e.offset %= e.peak, i.offset %= i.peak;
        compute_peak(&p, &e, &partial);
        compute_peak(&partial, &i, &final);
        day -= day < final.offset ? final.offset : final.peak + final.offset;
        printf("Case %d: the next triple peak occurs in %d days.\n", ++test, 
                -day);
    }
    return EXIT_SUCCESS;
}
