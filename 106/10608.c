/* 10608
 * Friends
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CITIZENS 30000

typedef struct citizen_s {
    struct citizen_s *set;
    int size;
} citizen_t, *citizen_p;

citizen_t citizen[MAX_CITIZENS];
int num_citizens;

/* Find a citizen set */
citizen_p find_set(citizen_p citizen) {
    if (citizen != citizen->set) {
        citizen->set = find_set(citizen->set);
    }
    return citizen->set;
}

/* Join two sets together */
void join_sets(citizen_p a, citizen_p b) {
    a = find_set(a), b = find_set(b);
    if (a != b) {
        a->set = b;
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_pairs;
        citizen_p largest;
        assert(scanf("%d %d", &num_citizens, &num_pairs) != EOF);
        for (i = 0; i < num_citizens; i++) {
            citizen[i].set = &citizen[i];
            citizen[i].size = 0;
        }
        for (i = 0; i < num_pairs; i++) {
            int a, b;
            assert(scanf("%d %d", &a, &b) != EOF);
            join_sets(&citizen[--a], &citizen[--b]);
        }
        for (i = 0, largest = &citizen[0]; i < num_citizens; i++) {
            citizen_p set = find_set(&citizen[i]);
            set->size++;
            if (set->size > largest->size) {
                largest = set;
            }
        }
        printf("%d\n", largest->size);
    }
    return 0;
}
