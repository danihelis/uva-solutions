/* 1595
 * Symmetry
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX_VALUE   20000
#define MIN_VALUE   (-MAX_VALUE)
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define EQUAL(a, b) (fabs(a - b) < 1e-3)

typedef struct {
    int x, y;
} point_t;

double median;

/* Compare two points */
int compare(const void *a, const void *b) {
    point_t *pa = (point_t *) a, *pb = (point_t *) b;
    if (pa->x == pb->x) return pa->x < median ? pa->y - pb->y : pb->y - pa->y;
    return pa->x - pb->x;
}

/* Main function */
int main() {
    int num_tests, n;
    point_t point[MAX_N];
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int i, j, lowest, highest;
        char symmetrical;
        assert(scanf("%d", &n) != EOF);
        for (i = 0, lowest = MAX_VALUE, highest = MIN_VALUE; i < n; i++) {
            assert(scanf("%d %d", &point[i].x, &point[i].y) != EOF);
            lowest = MIN(lowest, point[i].x);
            highest = MAX(highest, point[i].x);
        }
        median = lowest + (highest - lowest) / 2.0;
        qsort(point, n, sizeof (point_t), compare);
        for (i = 0, j = n - 1, symmetrical = 1; 
                symmetrical && i < j && !EQUAL(point[i].x, median); i++, j--) {
            double middle = (point[j].x - point[i].x) / 2.0 + point[i].x;
            symmetrical = point[i].y == point[j].y && EQUAL(middle, median);
        }
        if (i == j) symmetrical &= EQUAL(point[i].x, median);
        printf("%s\n", symmetrical ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
