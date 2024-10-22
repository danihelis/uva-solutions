/* 10911
 * Forming Quiz Teams
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TEAMS       8
#define MAX_STUDENTS    (2 * MAX_TEAMS)
#define MAX_SETS        (1 << MAX_STUDENTS)

#define SQUARE(x)           ((x) * (x))
#define DISTANCE(p1, p2)    (sqrt(SQUARE((p1).x - (p2).x) + SQUARE((p1).y - (p2).y)))

typedef struct {
    int x, y;
} point_t, *point_p;

point_t student[MAX_STUDENTS];
double solution[MAX_SETS];
char solution_set[MAX_SETS];
int num_teams;

/* Calculate the best distance between houses for a set of students */
double best_solution(int set) {
    if (solution_set[set]) {
        return solution[set];
    }
    else {
        int i, first = -1, odd_set, new_set;
        double distance, best = -1;
        for (i = 0; i < 2 * num_teams; i++) {
            if (set & (1 << i)) {
                if (first == -1) {
                    first = i;
                    odd_set = set ^ (1 << i);
                    continue;
                }
                new_set = odd_set ^ (1 << i);
                distance = DISTANCE(student[first], student[i]) + best_solution(new_set);
                if (best == -1 || distance < best) {
                    best = distance;
                }
            }
        }
        assert(best != -1);
        solution_set[set] = 1;
        solution[set] = best;
        return best;
    }
}

/* Main function */
int main() {
    int test = 1;
    while (scanf("%d", &num_teams) != EOF && num_teams > 0) {
        int i;
        memset(solution_set, 0, MAX_SETS);
        solution[0] = 0, solution_set[0] = 1;
        for (i = 0; i < num_teams * 2; i++) {
            assert(scanf(" %*s %d %d", &student[i].x, &student[i].y) != EOF);
        }
        printf("Case %d: %.2f\n", test++, best_solution((1 << (2 * num_teams)) - 1));
    }
    return 0;
}
