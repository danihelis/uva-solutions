/* 10324
 * Zeros and Ones
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    1000000
#define MAX_STRING  (MAX_SIZE + 2)

typedef struct {
    int start, end;
} interval_t;

interval_t interval[MAX_SIZE];
int num_intervals;

/* Compute intervals */
void compute_intervals(char string[]) {
    int i, n;
    char *s, last;
    for (s = string, i = 0, n = 0, last = 0; *s != 0; i++, s++)
        if (*s != last) {
            if (n > 0)
                interval[n - 1].end = i;
            interval[n++].start = i;
            last = *s;
        }
    assert(n > 0);
    interval[n - 1].end = i;
    num_intervals = n;
}

/* Binary search interval */
interval_t * find(int init) {
    int start = 0, end = num_intervals;
    while (start < end) {
        int middle = (start + end) / 2;
        if (interval[middle].start == init)
            return &interval[middle];
        else if (interval[middle].start < init)
            start = middle + 1;
        else
            end = middle;
    }
    assert(start > 0);
    return &interval[start - 1];
}

/* Main function */
int main() {
    int n, test = 0;
    char string[MAX_STRING];
    while (scanf(" %s", string) != EOF) {
        printf("Case %d:\n", ++test);
        compute_intervals(string);
        assert(scanf("%d", &n) != EOF);
        for (; n > 0; n--) {
            interval_t q, *i;
            assert(scanf("%d %d", &q.start, &q.end) != EOF);
            if (q.start > q.end) {
                int swap = q.start;
                q.start = q.end;
                q.end = swap;
            }
            i = find(q.start);
            printf("%s\n", q.end < i->end ? "Yes" : "No");
        }
    }
    return EXIT_SUCCESS;
}
