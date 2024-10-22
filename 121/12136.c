/* 12136
 * Schedule of a Married Man
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    int hour, min;
} hour_t;

#define READ(h)         assert(scanf("%d:%d", &(h).hour, &(h).min) == 2)
#define GREATER(h1, h2) (h1.hour > h2.hour || (h1.hour == h2.hour && \
                            h1.min > h2.min))

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        hour_t meet_start, meet_end, wife_start, wife_end;
        int exclusive;
        READ(wife_start);
        READ(wife_end);
        READ(meet_start);
        READ(meet_end);
        exclusive = GREATER(meet_start, wife_end) ||
            GREATER(wife_start, meet_end);
        printf("Case %d: %s Meeting\n", test, exclusive ? "Hits" : "Mrs");
    }
    return EXIT_SUCCESS;
}
