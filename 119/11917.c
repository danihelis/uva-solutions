/* 11917
 * Do Your Own Homework
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_STRING  25

typedef struct {
    char name[MAX_STRING];
    int time;
} subject_t;

subject_t subject[MAX_N], *dict[MAX_N];
int num_subjects;

/* Find or insert new subject */
int find_or_insert(char *name, int time) {
    int start = 0, end = num_subjects;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(name, dict[middle]->name);
        if (cmp == 0)
            return dict[middle]->time;
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    if (time < 0)
        return 10000 /* infinity */;
    strcpy(subject[num_subjects].name, name);
    subject[num_subjects].time = time;
    for (end = num_subjects; end > start; end--)
        dict[end] = dict[end - 1];
    dict[start] = &subject[num_subjects++];
    return time;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int n, t;
        char name[MAX_STRING];
        assert(scanf("%d", &n) == 1);
        for (num_subjects = 0; n > 0; n--) {
            assert(scanf(" %s %d", name, &t) == 2);
            find_or_insert(name, t);
        }
        assert(scanf("%d %s", &n, name) == 2);
        t = find_or_insert(name, -1);
        printf("Case %d: ", test);
        if (t <= n)
            puts("Yesss");
        else if (t <= n + 5)
            puts("Late");
        else
            puts("Do your own homework!");
    }
    return EXIT_SUCCESS;
}
