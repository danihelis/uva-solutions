/* 11503
 * Virtual Friends
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_FRIENDS 200000
#define MAX_NAME 30

typedef char string_t[MAX_NAME];

typedef struct friend_s {
    string_t name;
    struct friend_s *set;
    int rank, size;
} friend_t, *friend_p;

friend_t friend[MAX_FRIENDS];
friend_p index[MAX_FRIENDS];
int num_friends;

/* Search for a friend or insert a new one */
friend_p get_friend(string_t *name) {
    int start = 0, end = num_friends;
    while (start < end) {
        int middle, comp;
        middle = (start + end) / 2;
        comp = strcmp(index[middle]->name, *name);
        if (comp == 0) {
            return index[middle];
        }
        else if (comp < 0) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    for (end = num_friends; end > start; end--) {
        index[end] = index[end - 1];
    }
    index[start] = &friend[num_friends++];
    strcpy(index[start]->name, *name);
    index[start]->set = index[start];
    index[start]->rank = 0;
    index[start]->size = 1;
    return index[start];
}

/* Find a friend set */
friend_p find_set(friend_p friend) {
    if (friend != friend->set) {
        friend->set = find_set(friend->set);
    }
    return friend->set;
}

/* Join two sets together */
friend_p join_sets(friend_p a, friend_p b) {
    a = find_set(a), b = find_set(b);
    if (a == b) {
        return a;
    }
    if (a->rank < b->rank) {
        a->set = b;
        b->size += a->size;
        return b;
    }
    b->set = a;
    a->size += b->size;
    a->rank += (b->rank == a->rank ? 1 : 0);
    return a;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_pairs;
        assert(scanf("%d", &num_pairs) != EOF);
        num_friends = 0;
        for (i = 0; i < num_pairs; i++) {
            string_t name_a, name_b;
            friend_p set;
            assert(scanf(" %s %s", name_a, name_b) != EOF);
            set = join_sets(get_friend(&name_a), get_friend(&name_b));
            printf("%d\n", set->size);
        }
    }
    return 0;
}
