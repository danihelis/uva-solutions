/* 12321
 * Gas Stations
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

typedef struct {
    int start, end, threshold;    
} segment_t;

segment_t segment[MAX_N], *used[MAX_N];
int length, num_segments;

/* Compare two segments */
int compare(const void *a, const void *b) {
    segment_t *pa = (segment_t *) a, *pb = (segment_t *) b;
    if (pa->start == pb->start) return pb->end - pa->end;
    return pa->start - pb->start;
}

/* Compute maximal useless segments */
int compute_useless() {
    int i, num_used;
    qsort(segment, num_segments, sizeof (segment_t), compare);
    if (segment[0].start > 0) return -1;
    num_used = 0;
    for (i = 0; i < num_segments; i++) {
        segment_t *s = &segment[i];
        if (num_used > 0 && s->end <= used[num_used - 1]->end) continue;
        if (num_used > 0 && s->start > used[num_used - 1]->end) return -1;
        while (num_used > 0 && s->start <= used[num_used - 1]->threshold) {
            num_used--;
        }
        s->threshold = num_used > 0 ? used[num_used - 1]->end : s->start;
        used[num_used++] = s;
    }
    if (used[num_used - 1]->end < length) return -1;
    return num_segments - num_used;
}

/* Main function */
int main() {
    while (scanf("%d %d", &length, &num_segments) != EOF && length > 0) {
        int i, x, radius;
        for (i = 0; i < num_segments; i++) {
            assert(scanf("%d %d", &x, &radius) != EOF);
            segment[i].start = MAX(0, x - radius);
            segment[i].end = MIN(length, x + radius);
        }
        printf("%d\n", compute_useless());
    }
    return EXIT_SUCCESS;
}
