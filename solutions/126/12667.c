/* 12667
 * Last Blood
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TEAMS       100
#define MAX_PROBLEMS    12

typedef struct {
    int time, index, team;
} solution_t;

solution_t solution[MAX_PROBLEMS][MAX_TEAMS];
int num_problems, num_teams;

/* Compare two solutions to sort by the latest first */
int compare(const void *a, const void *b) {
    solution_t *pa = (solution_t *) a, *pb = (solution_t *) b;
    return pa->time == pb->time ? pb->index - pa->index : pb->time - pa->time;
}

/* Main function */
int main() {
    int i, t, num_submissions;
    assert(scanf("%d %d %d", &num_problems, &num_teams, &num_submissions) == 3);
    for (i = 0; i < num_problems; i++) {
        for (t = 0; t < num_teams; t++) {
            solution_t *s = &solution[i][t];
            s->time = s->index = 0, s->team = t + 1;
        }
    }
    for (i = 1; i <= num_submissions; i++) {
        char problem, response;
        int time, team;
        solution_t *pset;
        assert(scanf("%d %d %c %c%*s", &time, &team, &problem, &response) == 4);
        if (response == 'N') continue;
        pset = solution[problem - 'A'], team--;
        if (pset[team].index > 0) continue;
        pset[team].time = time, pset[team].index = i;
    }
    for (i = 0; i < num_problems; i++) {
        solution_t *last;
        qsort(solution[i], num_teams, sizeof (solution_t), compare);
        printf("%c ", i + 'A');
        last = &solution[i][0];
        if (last->index == 0) printf("- -\n");
        else printf("%d %d\n", last->time, last->team);
    }
    return EXIT_SUCCESS;
}
