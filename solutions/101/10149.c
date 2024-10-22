/*
 * 10149
 * Yahtzee
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DICE 5
#define DIE_SIZE 6
#define NUM_THROWS 13

#define FIVE_OF_A_KIND_PONTUATION 50
#define FULL_HOUSE_PONTUATION 40
#define SHORT_STRAIGHT_PONTUATION 25
#define LONG_STRAIGHT_PONTUATION 35
#define BONUS_PONTUATION 35
#define BONUS_THRESHOLD 63

#define THROW_SET_SIZE (1 << NUM_THROWS)
#define FULL_THROW_SET (THROW_SET_SIZE - 1)

typedef struct {
    int points;
    int previous;
} optimum_t;
optimum_t optimum_table[NUM_THROWS][THROW_SET_SIZE];

typedef enum {
    ONES = 0,
    TWOS,
    THREES,
    FOURS,
    FIVES,
    SIXES,
    CHANCE,
    THREE_OF_A_KIND,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
    SHORT_STRAIGHT,
    LONG_STRAIGHT,
    FULL_HOUSE
} kind_t;

typedef struct {
    int die[NUM_DICE];
} throw_t;
throw_t throw[NUM_THROWS];

typedef struct {
    int throw, points;
} game_t;

typedef struct {
    game_t game[NUM_THROWS];
    int num_games;
} combination_t;
combination_t combination[NUM_THROWS];


/* Sort the games of a combination by points */
int compare_points(const void *a, const void *b) {
    return ((game_t *) b)->points - ((game_t *) a)->points;
}


/* Count points for each throw */ 
#define ADD_THROW_TO_COMBINATION(c, t, p) \
    combination[c].game[combination[c].num_games].throw = (1 << t); \
    combination[c].game[combination[c].num_games].points = p; \
    combination[c].num_games++
void count_poins() {
    int c, d, t;
    int count[DIE_SIZE], sum_up, uniques;

    for (c = 0; c < NUM_THROWS; c++) {
        combination[c].num_games = 0;
    }

    for (t = 0; t < NUM_THROWS; t++) {
        int fh;
        
        /* Count repetitions */
        memset(count, 0, DIE_SIZE * sizeof (int));
        sum_up = 0;
        for (d = 0; d < NUM_DICE; d++) {
            count[throw[t].die[d] - 1]++;
            sum_up += throw[t].die[d];
        }
        
        /* Check for repetition patterns */
        uniques = 0;        
        for (c = 0; c < DIE_SIZE; c++) {
            switch (count[c]) {
                case 5:
                    ADD_THROW_TO_COMBINATION(FIVE_OF_A_KIND, t, FIVE_OF_A_KIND_PONTUATION);
                case 4:
                    ADD_THROW_TO_COMBINATION(FOUR_OF_A_KIND, t, sum_up);
                case 3:
                    ADD_THROW_TO_COMBINATION(THREE_OF_A_KIND, t, sum_up);
                    for (fh = 0; fh < DIE_SIZE && count[fh] != 1; fh++) {
                        if (count[fh] == 2) {
                            ADD_THROW_TO_COMBINATION(FULL_HOUSE, t, FULL_HOUSE_PONTUATION);
                            break;
                        }
                    }
                case 2:
                case 1:
                    ADD_THROW_TO_COMBINATION(c, t, count[c] * (c + 1));
                    if (count[c] == 1) {
                        uniques++;
                    }
            }
        }
        ADD_THROW_TO_COMBINATION(CHANCE, t, sum_up);
        
        /* Check for sequences */
        if (count[THREES] >= 1 && count[FOURS] >= 1) {
            if ((count[ONES] >= 1 && count[TWOS] >= 1) ||
                    (count[TWOS] >= 1 && count[FIVES] >= 1) ||
                    (count[FIVES] >= 1 && count[SIXES] >= 1)) {
                ADD_THROW_TO_COMBINATION(SHORT_STRAIGHT, t, SHORT_STRAIGHT_PONTUATION);
            }
        }
        if (uniques == NUM_DICE && (count[ONES] == 0 || count[SIXES] == 0)) {
            ADD_THROW_TO_COMBINATION(LONG_STRAIGHT, t, LONG_STRAIGHT_PONTUATION);
        }
    }

    /* Sort the games of each combination by points */
    for (c = 0; c < NUM_THROWS; c++) {
        qsort(combination[c].game, combination[c].num_games, sizeof (game_t), compare_points);
    }
    
}


/* Given a set of throws, defines the best throw for a given category through recursion (D.P.) */
int get_best_thrown(int c, int throw_set) {
    int g, sum;

    /* Use throws from set that gives point */
    for (g = 0; g < combination[c].num_games; g++) {
        int is_in = throw_set & combination[c].game[g].throw;
        if (is_in != 0) {
            int new_set = throw_set & (~ is_in);
            sum = combination[c].game[g].points;
            if (c > 0) {
                sum += (optimum_table[c - 1][new_set].points != -1 ? 
                    optimum_table[c - 1][new_set].points : get_best_thrown(c - 1, new_set));
                if (c == SIXES && optimum_table[c - 1][new_set].points < BONUS_THRESHOLD && 
                        sum >= BONUS_THRESHOLD) {
                    sum += BONUS_PONTUATION;
                }
            }
            if (sum > optimum_table[c][throw_set].points) {
                optimum_table[c][throw_set].points = sum;
                optimum_table[c][throw_set].previous = new_set;
            }
        }
    }

    /* Use not throws at all */
    if (c > 0) {
        sum = (optimum_table[c - 1][throw_set].points != -1 ? optimum_table[c - 1][throw_set].points : 
                get_best_thrown(c - 1, throw_set));
    }
    else {
        sum = 0;
    }
    if (sum > optimum_table[c][throw_set].points) {
        optimum_table[c][throw_set].points = sum;
        optimum_table[c][throw_set].previous = throw_set;
    }
    return optimum_table[c][throw_set].points;
}


/* Print resulting values attributed to combinations */
#define MAXIMUM_POINTS_WITH_NO_BONUS 30
void obtain_and_print_result() {
    int c, index, points[NUM_THROWS], bonus, sum;
    
    sum = get_best_thrown(NUM_THROWS - 1, FULL_THROW_SET);
    bonus = 0;

    /* Recover pontuation through memoization */
    index = FULL_THROW_SET;
    for (c = NUM_THROWS - 1; c >= 0; c--) {
        points[c] = optimum_table[c][index].points;
        if (c > 0) {
            index = optimum_table[c][index].previous;
            points[c] -= optimum_table[c - 1][index].points;
            if (c <= SIXES && points[c] > MAXIMUM_POINTS_WITH_NO_BONUS) {
                bonus = BONUS_PONTUATION;
                points[c] -= bonus;
            }
        }
    }

    /* Print pontuation */
    for (c = 0; c < NUM_THROWS; c++) {
        printf("%d ", points[c]);
    }
    printf("%d %d\n", bonus, sum);
}


/* Main program */
int main() {
    int d, t;
    while (scanf("%d", &t) != EOF) {

        /* Read data */
        throw[0].die[0] = t;
        for (d = 1; d < NUM_DICE; d++) {
            assert(scanf("%d", &throw[0].die[d]) != EOF);
        }
        for (t = 1; t < NUM_THROWS; t++) {
            for (d = 0; d < NUM_DICE; d++) {
                assert(scanf("%d", &throw[t].die[d]) != EOF);
            }
        }
        count_poins();

        /* Clear dynamic programming table and print result, calculating the values there in */
        memset(optimum_table, 0xFF, sizeof (optimum_t) * NUM_THROWS * THROW_SET_SIZE);
        obtain_and_print_result();
    }

    return 0;
}
