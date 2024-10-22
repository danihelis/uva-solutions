/* 10763
 * Foreign Exchange
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    500000

typedef struct {
    int a, b, signal;
} student_t, *student_p;

student_t student[MAX_SIZE];
int num_students;

/* Compare two students */
int compare(const void *a, const void *b) {
    student_p x = (student_p) a, y = (student_p) b;
    return (x->a == y->a ? x->b - y->b : x->a - y->a);
}

/* Main function */
int main() {
    while (scanf("%d", &num_students) != EOF && num_students > 0) {
        int i, score, possible;
        for (i = 0; i < num_students; i++) {
            student_p s = &student[i];
            assert(scanf("%d %d", &s->a, &s->b) != EOF);
            s->signal = 1;
            if (s->a > s->b) {
                int swap = s->a;
                s->a = s->b;
                s->b = swap;
                s->signal = -1;
            }
        }
        if (num_students % 2 == 1) {
            printf("NO\n");
            continue;
        }
        qsort(student, num_students, sizeof (student_t), compare);
        for (i = 0, possible = 1; possible && i < num_students; ) {
            student_p s = &student[i], p = &student[i + 1];
            for (score = s->signal, i++; i < num_students && s->a == p->a && s->b == p->b; 
                    score += p->signal, p++, i++)
                ;
            possible = (score == 0);
        }
        printf("%s\n", (possible ? "YES" : "NO"));
    }
    return 0;
}
