/* 1047
 * Zones
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20
#define MAX_COMMON  10

typedef struct {
    int served, used;
} common_t;

typedef struct {
    int served;
    int common[MAX_COMMON], num_common;
} tower_t;

tower_t tower[MAX_N];
common_t common[MAX_COMMON];
int num_towers, num_common, max_used;

/* Compute best coverage */
int best_coverage(int index, int num_used, int *sol) {
    int i, sum;
    tower_t *t = &tower[index];
    assert(index < num_towers);
    sol[num_used] = index;
    sum = t->served;
    for (i = 0; i < t->num_common; i++) {
        common_t *c = &common[t->common[i]];
        if (c->used)
            sum -= c->served;
    }
    if (num_used + 1 < max_used) {
        char used[MAX_COMMON];
        for (i = 0; i < t->num_common; i++) {
            common_t *c = &common[t->common[i]];
            used[i] = c->used;
            c->used = 1;
        }
        sum += best_coverage(index + 1, num_used + 1, sol);
        for (i = 0; i < t->num_common; i++)
            common[t->common[i]].used = used[i];
    }
    if (num_towers - index - 1 >= max_used - num_used) {
        int another[MAX_N];
        int without = best_coverage(index + 1, num_used, another);
        if (without > sum) {
            sum = without;
            for (i = num_used; i < max_used; i++)
                sol[i] = another[i];
        }
    }
    return sum;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d %d", &num_towers, &max_used) != EOF && num_towers > 0) {
        int i, best, solution[MAX_N];
        for (i = 0; i < num_towers; i++) {
            tower_t *t = &tower[i];
            assert(scanf("%d", &t->served) != EOF);
            t->num_common = 0;
        }
        assert(scanf("%d", &num_common) != EOF);
        for (i = 0; i < num_common; i++) {
            int total, t;
            common_t *c = &common[i];
            assert(scanf("%d", &total) != EOF);
            for (; total > 0; total--) {
                assert(scanf("%d", &t) != EOF);
                t--;
                tower[t].common[tower[t].num_common++] = i;
            }
            assert(scanf("%d", &c->served) != EOF);
            c->used = 0;
        }
        best = best_coverage(0, 0, solution);
        printf("Case Number  %d\nNumber of Customers: %d\n"
               "Locations recommended:", ++test, best);
        for (i = 0; i < max_used; i++)
            printf(" %d", solution[i] + 1);
        printf("\n\n");
    }
    return EXIT_SUCCESS;
}
