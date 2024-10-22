/* 11459
 * Snakes and Ladders
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PLAYERS     1000000
#define MAX_CELLS       100

typedef struct {
    int start, end;
} ladder_t;

ladder_t ladder[MAX_CELLS];
int position[MAX_PLAYERS];

/* Compare two ladders */
int compare(const void *a, const void * b) {
    return ((ladder_t *) a)->start - ((ladder_t *) b)->start;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int player, i, num_players, num_ladders, num_dice, end;
        assert(scanf("%d %d %d", &num_players, &num_ladders, &num_dice) != EOF);
        for (i = 0; i < num_players; i++) {
            position[i] = 1;
        }
        for (i = 0; i < num_ladders; i++) {
            assert(scanf("%d %d", &ladder[i].start, &ladder[i].end) != EOF);
        }
        qsort(ladder, num_ladders, sizeof (ladder_t), compare);
        for (i = 0, player = -1, end = 0; i < num_dice; i++) {
            int die;
            assert(scanf("%d", &die) != EOF);
            if (!end) {
                ladder_t *lad, key;
                player = (player + 1) % num_players;
                position[player] += die;
                key.start = position[player];
                lad = bsearch(&key, ladder, num_ladders, sizeof (ladder_t), compare);
                if (lad != NULL) {
                    position[player] = lad->end;
                }
                if (position[player] >= MAX_CELLS) {
                    end = 1;
                    position[player] = MAX_CELLS;
                }
            }
        }
        for (i = 0; i < num_players; i++) {
            printf("Position of player %d is %d.\n", i + 1, position[i]);
        }
    }
    return 0;
}
