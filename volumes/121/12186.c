/* 12186
 * Another Crisis
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES   100001

typedef struct employee_s {
    struct employee_s *subordinates, *next_colleague;
} employee_t;

employee_t employees[MAX_EMPLOYEES];
int num_employees;
int percentage;

/* Read structure */
void read_employees() {
    int i, boss;
    employee_t *e, *b;
    for (i = 0; i <= num_employees; i++) {
        e = &employees[i];
        e->subordinates = e->next_colleague = NULL;
    }
    for (i = 1; i <= num_employees; i++) {
        assert(scanf("%d", &boss) == 1);
        b = &employees[boss], e = &employees[i];
        e->next_colleague = b->subordinates;
        b->subordinates = e;
    }
}

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compute workers needed to fulfill petition */
int get_workers_needed(employee_t *employee) {
    if (employee->subordinates == NULL) return 1;
    else {
        int workers[MAX_EMPLOYEES];
        int num_subordinates = 0;
        int needed;
        int i, total;
        employee_t *s = employee->subordinates;
        while (s != NULL) {
            workers[num_subordinates++] = get_workers_needed(s);
            s = s->next_colleague;
        }
        qsort(workers, num_subordinates, sizeof (int), compare);
        needed = (num_subordinates * percentage + 99) / 100;
        for (i = total = 0; i < needed; i++) {
            total += workers[i];
        }
        return total;
    }
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_employees, &percentage) == 2 && num_employees) {
        read_employees();
        printf("%d\n", get_workers_needed(&employees[0]));
    }
    return EXIT_SUCCESS;
}
