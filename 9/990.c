/* 990
 * Diving for gold
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TIME 1010
#define MAX_TREASURES 30

typedef struct {
    int depth, gold;
} treasure_t, *treasure_p;

typedef struct {
    int gold, set, total;
} solution_t, *solution_p;

treasure_t treasure[MAX_TREASURES];
int num_treasures;

/* Obtain best solution to treasure hunting */
solution_p get_solution(int time, int weight) {
    static solution_t table[MAX_TIME], reference[MAX_TIME];
    int i, t;
    memset(table, 0, (time + 1) * sizeof (solution_t));
    for (i = 0; i < num_treasures; i++) {
        treasure_p lot = &treasure[i];
        memcpy(reference, table, (time + 1) * sizeof (solution_t));
        for (t = lot->depth * weight; t <= time; t++) {
            int remain = t - lot->depth * weight;
            if (lot->gold + reference[remain].gold > table[t].gold) {
                table[t].gold = reference[remain].gold + lot->gold;
                table[t].total = reference[remain].total + 1;
                table[t].set = reference[remain].set | (1 << i);
            }
        }
    }
    return &table[time];
}

/* Print treasures from solution set */
void print_treasures(int set, int total) {
    int i;
    for (i = 0; i < num_treasures; i++) {
        if (set & (1 << i)) {
            printf("%d %d\n", treasure[i].depth, treasure[i].gold);
            total--;
        }
    }
    assert(total == 0);
}

/* Main function */
int main() {
    int time, weight, i, first_time = 1;
    while (scanf("%d %d", &time, &weight) != EOF) {
        solution_p solution;
        assert(scanf("%d", &num_treasures) != EOF);
        for (i = 0; i < num_treasures; i++) {
            assert(scanf("%d %d", &treasure[i].depth, &treasure[i].gold) != EOF);
        }
        solution = get_solution(time, 3 * weight);
        (first_time ? first_time = 0 : printf("\n"));
        printf("%d\n%d\n", solution->gold, solution->total);
        print_treasures(solution->set, solution->total);
    }
    return 0;
}
