/* 11729
 * Commando War
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

typedef struct {
    int brief, task;
} plan_t;

/* Compare plans */
int compare(const void *a, const void *b) {
    return ((plan_t *) b)->task - ((plan_t *) a)->task;
}

/* Main function */
int main() {
    int n, test = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        plan_t plan[MAX_N];
        int i, time, briefing;
        for (i = 0; i < n; i++)
            assert(scanf("%d %d", &plan[i].brief, &plan[i].task) == 2);
        qsort(plan, n, sizeof (plan_t), compare);
        for (i = 0, briefing = time = 0; i < n; i++) {
            briefing += plan[i].brief;
            time = MAX(time, briefing + plan[i].task);
        }
        printf("Case %d: %d\n", ++test, time);
    }
    return EXIT_SUCCESS;
}
