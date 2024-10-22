/* 1197
 * The Suspects
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   30000

typedef void* set;

set group[MAX_N];

/* Get set */
set get_set(set *s) {
    if (*s != s)
        *s = get_set(*s);
    return *s;
}

/* Join sets */
void join_sets(set *a, set *b) {
    a = get_set(a);
    *a = get_set(b);
}

/* Main function */
int main() {
    int n, m, i, total;
    set actual;
    while (scanf("%d %d", &n, &m) == 2 && n > 0) {
        for (i = 0; i < n; i++)
            group[i] = &group[i];
        for (; m > 0; m--) {
            int len, member;
            assert(scanf("%d %d", &len, &member) == 2);
            actual = get_set(&group[member]);
            for (len--; len > 0; len--) {
                assert(scanf("%d", &member) == 1);
                join_sets(&actual, &group[member]);
            }
        }
        actual = get_set(group[0]);
        for (i = total = 1; i < n; i++)
            total += get_set(group[i]) == actual ? 1 : 0;
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
