/*
 * 10026
 * Shoemaker's Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TASKS 1000
typedef struct {
    int id, delay, cost;
} task_t;
task_t task[MAX_TASKS];
int num_tasks;


/* Compare two tasks by day cost */
int compare_daily_cost(const void *a, const void *b) {
    task_t *x = (task_t *) a, *y = (task_t *) b;
    long val_x = x->cost * y->delay, val_y = y->cost * x->delay;
    if (val_x == val_y) {
        return x->id - y->id;
    }
    return val_y - val_x;
}


/* Main function */
int main() {
    int test, num_tests;
    int i;

    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        if (test > 0) {
            printf("\n");
        }

        assert(scanf("%d", &num_tasks) != EOF);
        for (i = 0; i < num_tasks; i++) {
            task[i].id = i + 1;
            assert(scanf("%d %d", &task[i].delay, &task[i].cost) != EOF);
        }

        qsort(task, num_tasks, sizeof (task_t), compare_daily_cost);
        for (i = 0; i < num_tasks; i++) {
            printf("%d%c", task[i].id, (i == num_tasks - 1 ? '\n' : ' '));
        }        
    }

    return 0;
}
