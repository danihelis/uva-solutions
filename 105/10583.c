/* 10583
 * Ubiquitous Religions
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STUDENTS 50000

typedef struct student_s {
    struct student_s *set;
    char visited;
} student_t, *student_p;

student_t student[MAX_STUDENTS];
int num_students;

/* Find a student set */
student_p find_set(student_p student) {
    if (student != student->set) {
        student->set = find_set(student->set);
    }
    return student->set;
}

/* Join two sets together */
void join_sets(student_p a, student_p b) {
    a = find_set(a), b = find_set(b);
    if (a != b) {
        a->set = b;
    }
}

/* Main function */
int main() {
    int i, test, num_pairs, num_sets;
    test = 0;
    while (scanf("%d %d", &num_students, &num_pairs) != EOF && 
            (num_students > 0 || num_pairs > 0)) {
        for (i = 0; i < num_students; i++) {
            student[i].set = &student[i];
            student[i].visited = 0;
        }
        for (i = 0; i < num_pairs; i++) {
            int a, b;
            assert(scanf("%d %d", &a, &b) != EOF);
            join_sets(&student[--a], &student[--b]);
        }
        for (i = 0, num_sets = 0; i < num_students; i++) {
            student_p set = find_set(student[i].set);
            if (!set->visited) {
                set->visited = 1;
                num_sets++;
            }
        }
        printf("Case %d: %d\n", ++test, num_sets);
    }
    return 0;
}
