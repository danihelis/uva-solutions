/* 735
 * Dart-a-Mania
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SCORE   60
#define MAX_DARTS   3
#define VALID(x)    ((x) <= 20 || (x) == 50 || ((x) % 2 == 0 && (x) <= 40) \
                        || ((x) % 3 == 0 && (x) <= 60))
#define CEIL(x,y)   (((x) + (y) - 1) / (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define DIFFS(x,y)    (score[x] != score[y] ? 1 : 0)

int permutations, combinations;
int score[MAX_DARTS];

/* Find combinations of score (A,B,C) such that A >= B >= C */
void find_combinations(int points, int max_score, int darts) {
    if (darts == 1) {
        assert(points <= max_score);
        if (VALID(points)) {
            int diff;
            combinations++;
            score[0] = points;
            diff = DIFFS(0, 1) + DIFFS(1, 2) + DIFFS(0, 2);
            permutations += diff == 0 ? 1 : diff == 2 ? 3 : 6;
        }
    }
    else {
        int k, low = CEIL(points, darts), high = MIN(points, max_score);
        for (k = low; k <= high; k++)
            if (VALID(k)) {
                score[darts - 1] = k;
                find_combinations(points - k, k, darts - 1);
            }
    }
}

/* Main function */
int main() {
    int points;
    while (scanf("%d", &points) != EOF && points > 0) {
        permutations = combinations = 0;
        find_combinations(points, MAX_SCORE, MAX_DARTS);
        if (combinations == 0)
            printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n",
                    points);
        else
            printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n"
                   "NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n",
                   points, combinations, points, permutations);
        for (points = 70; points > 0; points--)
            printf("*");
        printf("\n");
    }
    printf("END OF OUTPUT\n");
    return EXIT_SUCCESS;
}
