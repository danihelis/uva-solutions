/* 11804
 * Argentina
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_PLAYERS 10
#define MAX_GROUP   5
#define MAX_STRING  25

typedef struct {
    char name[MAX_STRING];
    int defense, attack;
} player_t, *player_p;

player_t player[NUM_PLAYERS];
player_p attack[MAX_GROUP], defense[MAX_GROUP], sorted[NUM_PLAYERS], extra[NUM_PLAYERS];

#define COMPARE_FUNCTION(name,statement) \
    int name(const void *a, const void *b) { \
        player_p x = *((player_p *) a), y = *((player_p *) b); \
        return (statement); \
    }
        
#define SELECT_PLAYER(is_attack,total,middle,field) do { \
        qsort(sorted, total, sizeof (player_p), compare_##field); \
        for (i = 0, num_extra = 0; i < total; i++) { \
            if (sorted[i]->field > sorted[middle]->field) { \
                if (is_attack) attack[num_attack++] = sorted[i]; \
                else defense[num_defense++] = sorted[i]; \
            } else if (num_##field < MAX_GROUP && sorted[i]->field == sorted[middle]->field) \
                extra[num_extra++] = sorted[i]; \
            else \
                if (is_attack) defense[num_defense++] = sorted[i]; \
                else attack[num_attack++] = sorted[i]; \
        } \
        assert(num_attack <= MAX_GROUP && num_defense <= MAX_GROUP); \
    } while (0)

#define PRINT_LIST(vector) do { \
        int i; \
        for (i = 0; i < MAX_GROUP; i++) \
            printf("%s%s", (i == 0 ? "(" : ", "), vector[i]->name); \
        printf(")\n"); \
    } while (0)

COMPARE_FUNCTION(compare_attack, y->attack - x->attack)
COMPARE_FUNCTION(compare_defense, y->defense - x->defense)
COMPARE_FUNCTION(compare_name, strcmp(x->name, y->name))

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, num_attack, num_defense, num_extra, group_size, remain_defense;
        for (i = 0; i < NUM_PLAYERS; i++) {
            assert(scanf(" %s %d %d", player[i].name, &player[i].attack, 
                        &player[i].defense) != EOF);
            sorted[i] = &player[i];
        }

        /* Determine those who are best at attack */
        num_attack = 0, num_defense = 0;
        SELECT_PLAYER(1, NUM_PLAYERS, MAX_GROUP, attack);

        /* Determine those who must attend defense */
        group_size = num_extra, remain_defense = MAX_GROUP - num_defense;    
        assert(remain_defense <= group_size);
        memcpy(sorted, extra, group_size * sizeof (player_p));
        SELECT_PLAYER(0, group_size, remain_defense, defense);

        /* Determine those who will attack because their names come first */
        qsort(extra, num_extra, sizeof (player_p), compare_name);
        for (i = 0; i < num_extra; i++) {
            if (num_attack < MAX_GROUP) {
                attack[num_attack++] = extra[i];
            }
            else {
                defense[num_defense++] = extra[i];
            }
        }

        assert(num_attack == num_defense && num_attack == MAX_GROUP);
        qsort(attack, MAX_GROUP, sizeof (player_p), compare_name);
        qsort(defense, MAX_GROUP, sizeof (player_p), compare_name);

        printf("Case %d:\n", test);
        PRINT_LIST(attack);
        PRINT_LIST(defense);
    }
    return 0;
}
