/* 12662
 * Good Teacher
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_STR     5

#define UNDEFINED   -1
#define LEFT        0
#define RIGHT       1
#define MIDDLE      2
#define PROPER      4

typedef struct {
    char name[MAX_STR];
    int index, relation, distance;
} student_t;

student_t student[MAX_N];
int n;

/* Define students' relations */
void define_relations() {
    int i, j, d;
    for (i = 0; i < n; i++) {
        student_t *known = &student[i];
        if (known->relation == PROPER) {
            known->distance = 0;
            for (j = i - 1, d = 1; j >= 0; j--, d++) {
                student_t *s = &student[j];
                if (s->relation == UNDEFINED || s->distance > d) {
                    s->relation = LEFT, s->distance = d;
                } else {
                    if (s->distance == d) s->relation = MIDDLE;
                    break;
                }
            }
            for (j = i + 1, d = 1; j < n; j++, d++) {
                student_t *s = &student[j];
                if (s->relation == UNDEFINED) {
                    s->relation = RIGHT, s->distance = d;
                } else break;
            }
        }
    }
}

/* Main function */
int main() {
    int i, queries;
    student_t *s;
    assert(scanf("%d", &n) == 1);
    for (i = 0; i < n; i++) {
        student_t *s = &student[i];
        assert(scanf(" %s", s->name) == 1);
        s->index = i, s->relation = s->name[0] == '?' ? UNDEFINED : PROPER;
    }
    define_relations();
    assert(scanf("%d", &queries) == 1);
    while (queries-- > 0) {
        assert(scanf("%d", &i) == 1);
        s = &student[--i];
        while (s->distance > 0) {
            if (s->relation == LEFT) {
                printf("left of ");
                s++;
            } else if (s->relation == RIGHT) {
                printf("right of ");
                s--;
            } else {
                printf("middle of %s and ", student[s->index - s->distance].name);
                s += s->distance;
            }
        }
        printf("%s\n", s->name);
    }
    return EXIT_SUCCESS;
}
