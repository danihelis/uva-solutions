/* 10020
 * Minimal coverage
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SEGMENTS        100000

typedef struct {
    int start, end;
} segment_t, *segment_p;

segment_t segment[MAX_SEGMENTS];
segment_p seg_ptr[MAX_SEGMENTS], solution[MAX_SEGMENTS];
int num_segments, sol_size;

/* Compare two pointers to segments */
int compare(const void *a, const void *b) {
    segment_p x = *((segment_p *) a), y = *((segment_p *) b);
    return x->start - y->start;
}

/* Cover the interval from 0 to last_end */
int cover(int last_end) {
    int i, threshold;
    segment_p cur, candidate;
    for (i = 0, threshold = 0, sol_size = 0, candidate = NULL; i < num_segments; i++) {
        cur = seg_ptr[i];
        if (cur->start <= threshold) {
            if (candidate == NULL || cur->end > candidate->end) {
                candidate = cur;
                if (candidate->end >= last_end) {
                    solution[sol_size++] = candidate;
                    break;
                }
            }
        }
        else {
            if (candidate == NULL) {
                return 0;
            }
            solution[sol_size++] = candidate;
            threshold = candidate->end;
            candidate = NULL;
            i--; /* re-evaluate curent segment */
        }
    }
    return 1;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int m;
        segment_t s;
        assert(scanf("%d", &m) != EOF);
        num_segments = 0;
        while (scanf("%d %d", &s.start, &s.end) != EOF && !(s.start == 0 && s.end == 0)) {
            segment[num_segments] = s;
            seg_ptr[num_segments] = &segment[num_segments];
            num_segments++;
        }
        qsort(seg_ptr, num_segments, sizeof (segment_p), compare);
        if (!cover(m)) {
            printf("0\n");
        }
        else {
            printf("%d\n", sol_size);
            for (m = 0; m < sol_size; m++) {
                printf("%d %d\n", solution[m]->start, solution[m]->end);
            }
        }
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
