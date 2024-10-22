/* 1193
 * Radar Installation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define EPSILON     1e-10

typedef struct {
    double start, end;
} range_t;

range_t range[MAX_N];
int num_ranges;

/* Compare two ranges */
int compare(const void *a, const void *b) {
    range_t *pa = (range_t *) a, *pb = (range_t *) b;
    return pa->end < pb->end ? -1 : 1;
}

/* Find minimum stations to cover all ranges */
int minimum_stations() {
    int i, stations;
    double last;
    qsort(range, num_ranges, sizeof (range_t), compare);
    for (i = stations = 0; i < num_ranges; i++) {
        range_t *r = &range[i];
        if (i == 0 || r->start > last) {
            stations++, last = r->end;
        }
    }
    return stations;
}

/* Main function */
int main() {
    int test = 0, radius;
    while (scanf("%d %d", &num_ranges, &radius) != EOF && num_ranges > 0) {
        int i, x, y, possible;
        for (i = 0, possible = 1; i < num_ranges; i++) {
            double length;
            assert(scanf("%d %d", &x, &y) != EOF);
            length = radius * radius - y * y;
            if (!possible || length < 0) possible = 0;
            else {
                length = sqrt(length);
                range[i].start = x - length, range[i].end = x + length;
            }            
        }
        printf("Case %d: %d\n", ++test, possible ? minimum_stations() : -1);
    }
    return EXIT_SUCCESS;
}
