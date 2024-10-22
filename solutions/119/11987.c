/* 11987
 * Almost Union-Find
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100000
#define MAX_2N  (2 * MAX_N)

typedef struct set_s {
    struct set_s *set;
    int count, sum;
} set_t;

set_t base[MAX_2N], *element[MAX_N];
int num_bases;

/* Get set */
set_t * get_set(set_t *elem) {
    if (elem->set == elem) return elem;
    elem->set = get_set(elem->set);
    return elem->set;
}

/* Join set */
void join_set(set_t *a, set_t *b) {
    a = get_set(a), b = get_set(b);
    if (a != b) {
        b->count += a->count, b->sum += a->sum;
        a->set = b;
    }
}

/* Create set */
set_t * create_set(int index) {
    set_t *b = &base[num_bases++];
    element[index] = b;
    b->set = b, b->count = 1, b->sum = index + 1;
    return b;
}

/* Move element to new set */
void move(int index, set_t* new) {
    set_t *old = get_set(element[index]);
    new = get_set(new);
    if (old != new) {
        old->count--, old->sum -= index + 1;
        join_set(create_set(index), new);
    }
}

/* Main function */
int main() {
    int num_sets, num_ops;
    while (scanf("%d %d", &num_sets, &num_ops) != EOF) {
        int i, a, b;
        for (i = num_bases = 0; i < num_sets; i++) {
            create_set(i);
        }
        while (num_ops-- > 0) {
            assert(scanf("%d %d", &i, &a) != EOF);
            if (i == 3) {
                set_t *s = get_set(element[--a]);
                printf("%d %d\n", s->count, s->sum);
            } else {
                assert(scanf("%d", &b) != EOF);
                --a, --b;
                if (i == 1) join_set(element[a], element[b]);
                else move(a, element[b]);
            }
        }
    }
    return EXIT_SUCCESS;
}
