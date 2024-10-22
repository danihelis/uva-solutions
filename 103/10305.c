/* 10305
 * Ordering Tasks
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TASKS   100

typedef struct {
    int before[MAX_TASKS];
    int index, total, printed;
} task_s, *task_p;

task_s task[MAX_TASKS];
int num_tasks;

/* Print order */
void print_order(task_p t, int *first) {
    int i;
    if (!t->printed) {
        t->printed = 1;
        for (i = 0; i < t->total; i++) {
            task_p b = &task[t->before[i]];
            if (!b->printed) {
                print_order(b, first);
            }
        }
        printf("%s%d", *first ? "" : " ", t->index + 1);
        *first = 0;
    }
}

/* Main function */
int main() {
    int i, first, num_entries;
    while (scanf("%d %d", &num_tasks, &num_entries) != EOF && num_tasks > 0) {
        for (i = 0; i < num_tasks; i++) {
            task_p t = &task[i];
            t->index = i, t->total = 0, t->printed = 0;
        }
        for (i = 0; i < num_entries; i++) {
            int before, after;
            assert(scanf("%d %d", &before, &after) != EOF);
            before--, after--;
            task[after].before[task[after].total++] = before;
        }
        for (i = 0, first = 1; i < num_tasks; i++) {
            print_order(&task[i], &first);
        }
        printf("\n");
    }
    return 0;
}
