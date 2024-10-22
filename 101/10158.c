/* 10158
 * War
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER 10000

typedef struct set_s {
    struct set_s *friend, *enemy;
} set_t, *set_p;

set_t set[MAX_NUMBER];
int num_sets;

/* Get friend set group */
set_p get_friend(set_p set) {
    if (set != set->friend) {
        set->friend = get_friend(set->friend);
    }
    return set->friend;
}

/* Get enemy set group */
set_p get_enemy(set_p set) {
    set_p group = get_friend(set);
    return (group->enemy == NULL ? NULL : get_friend(group->enemy));
}

/* Join two frienly sets */
set_p join(set_p a, set_p b) {
    set_p friend_a, friend_b, enemy_of_a, enemy_of_b;
    if (a == NULL || b == NULL) {
        return NULL;
    }
    friend_a = get_friend(a), friend_b = get_friend(b);
    enemy_of_a = get_enemy(a), enemy_of_b = get_enemy(b);
    if (friend_a != friend_b) {
        friend_a->friend = friend_b;
        if (enemy_of_b == NULL) {
            friend_b->enemy = enemy_of_a;
        }
        else {
            join(enemy_of_b, enemy_of_a);
        }
    }
    assert(get_enemy(a) == get_enemy(b));
    return friend_b;
}

/* Main function */
int main() {
    int i, a, b, question;
    assert(scanf("%d", &num_sets) != EOF);
    for (i = 0; i < num_sets; i++) {
        set[i].friend = &set[i];
        set[i].enemy = NULL;
    }
    while (scanf("%d %d %d", &question, &a, &b) != EOF && question > 0) {
        set_p group_a = get_friend(&set[a]), group_b = get_friend(&set[b]);
        set_p enemy_of_a = get_enemy(&set[a]), enemy_of_b = get_enemy(&set[b]);
        switch (question) {
            case 1:
                if (group_a == enemy_of_b || group_b == enemy_of_a) {
                    printf("-1\n");
                }
                else if (group_a != group_b) {
                    join(group_a, group_b);
                }
                break;
            case 2:
                if (group_a == group_b || (enemy_of_a == enemy_of_b && enemy_of_a != NULL)) {
                    printf("-1\n");
                }
                else if (group_a != enemy_of_b && group_b != enemy_of_a) {
                    if (enemy_of_a == NULL) {
                        group_a->enemy = group_b;
                    }
                    if (enemy_of_b == NULL) {
                        group_b->enemy = group_a;
                    }
                    join(enemy_of_a, group_b);
                    join(enemy_of_b, group_a);
                    assert(get_enemy(group_a) == get_friend(group_b) && 
                            get_enemy(group_b) == get_friend(group_a));
                }
                break;
            case 3:
                printf("%d\n", (group_a == group_b ? 1 : 0));
                break;
            case 4:
                printf("%d\n", (group_a == enemy_of_b || group_b == enemy_of_a ? 1 : 0));
                break;
        }
    }
    return 0;
}
