/* 607
 * Scheduling Lectures
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LECTURES 1010
#define INFINITY (MAX_LECTURES + 1)

#define SQUARE(x) ((x) * (x))

typedef struct {
    int score, days;
} solution_t, *solution_p;

solution_t solution[MAX_LECTURES];
int lecture[MAX_LECTURES];
int num_lectures;

/* Compute the minimum days for lectures and best score */
void compute_solution(int day, int happy) {
    int i, k;
    solution[num_lectures].days = 0;
    solution[num_lectures].score = 0;
    for (i = num_lectures - 1; i >= 0; i--) {
        int time = 0, score;
        solution_p sol = &solution[i], remain;
        sol->days = INFINITY;
        for (k = i; k < num_lectures && time < day; k++) {
            time += lecture[k];
            if (time > day) {
                break;
            }
            score = (day == time ? 0 : day - time <= 10 ? happy : SQUARE(day - time - 10));
            remain = &solution[k + 1];
            if (remain->days + 1 < sol->days || (remain->days + 1 == sol->days &&
                        remain->score + score < sol->score)) {
                sol->days = remain->days + 1;
                sol->score = remain->score + score;
            }
        }
    }
}

/* Main function */
int main() {
    int test = 1;
    while (scanf("%d", &num_lectures) != EOF && num_lectures > 0) {
        int i, lecture_time, happy_value;
        assert(scanf("%d %d", &lecture_time, &happy_value) != EOF);
        for (i = 0 ; i < num_lectures; i++) {
            assert(scanf("%d", &lecture[i]) != EOF);
        }
        compute_solution(lecture_time, -happy_value);
        printf("%sCase %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n",
                (test > 1 ? "\n" : ""), test, solution[0].days, solution[0].score);
        test++;
    }
    return 0;
}
