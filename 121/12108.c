/* 12108
 * Extraordinarily Tired Students
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CYCLES  2520
#define MAX_N       10

typedef struct {
    int awaken, sleeping, state;
} student_t;

student_t student[MAX_N];
int num_students;

/* Find cycle when every student is awaken */
int get_minimum_cyle() {
    int i, cycle, awakening;
    for (cycle = 1, awakening = 0; awakening || cycle <= MAX_CYCLES; cycle++) {
        int awaken = 0;
        for (i = 0; i < num_students; i++) {
            student_t *s = &student[i];
            awaken += s->state <= s->awaken ? 1 : 0;
        }
        if (awaken == num_students) return cycle;
        awakening = awaken >= (num_students + 1) / 2;
        for (i = 0; i < num_students; i++) {
            student_t *s = &student[i];
            if (s->state == s->awaken && awakening) s->state = 1;
            else s->state = (s->state % (s->awaken + s->sleeping)) + 1;
        }
    }
    return -1;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_students) != EOF && num_students > 0) {
        int i;
        for (i = 0; i < num_students; i++) {
            student_t *s = &student[i];
            assert(scanf("%d %d %d", &s->awaken, &s->sleeping, &s->state) != EOF);
        }
        printf("Case %d: %d\n", ++test, get_minimum_cyle());
    }
    return EXIT_SUCCESS;
}
