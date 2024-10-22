/* 1160
 * X-Plosives
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100001

typedef struct set_s {
    struct set_s * set;
} set_t;

set_t set[MAX_N];

/* Get set */
set_t * get_set(set_t *s) {
    if (s->set != s)
        s->set = get_set(s->set);
    return s->set;
}

/* Join sets */
void join_sets(set_t *a, set_t *b) {
    set_t *s = get_set(a);
    s->set = get_set(b);
}

/* Main function */
int main() {
    while (!feof(stdin)) {
        int a, b, refuses = 0;
        memset(set, 0, sizeof (set));
        while (scanf("%d ", &a) == 1 && a >= 0) {
            assert(scanf("%d", &b) == 1);
            if (set[a].set == NULL)
                set[a].set = &set[a];
            if (set[b].set == NULL) 
                set[b].set = &set[b];
            if (get_set(&set[a]) == get_set(&set[b]))
                refuses++;
            else
                join_sets(&set[a], &set[b]);
        }
        printf("%d\n", refuses);
    }
    return EXIT_SUCCESS;
}
