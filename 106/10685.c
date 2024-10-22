/* 10685
 * Nature
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       5000
#define MAX_R       5000
#define MAX_STR     32

typedef struct animal_s {
    char name[MAX_STR];
    struct animal_s *set;
    int count;
} animal_t;

animal_t animal[MAX_N], *dict[MAX_N];
int size;

/* Get set */
animal_t * get_set(animal_t *s) {
    if (s->set != s)
        s->set = get_set(s->set);
    return s->set;
}

/* Join sets */
void join_sets(animal_t *a, animal_t *b) {
    animal_t *s = get_set(a);
    s->set = get_set(b);
}

/* Find or insert */
animal_t * find_insert(char *name) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(name, dict[middle]->name);
        if (cmp == 0)
            return dict[middle];
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    strcpy(animal[size].name, name);
    animal[size].set = &animal[size];
    animal[size].count = 0;
    for (end = size; end > start; end--)
        dict[end] = dict[end - 1];
    dict[start] = &animal[size++];
    return dict[start];
}

/* Find largest set */
int largest_set() {
    int i, max;
    for (i = max = 0; i < size; i++) {
        animal_t *s = get_set(dict[i]);
        s->count++;
        if (s->count > max)
            max = s->count;
    }
    return max;
}

/* Main function */
int main() {
    int n, r;
    while (scanf("%d %d", &n, &r) == 2 && n > 0) {
        int i;
        for (i = size = 0; i < n; i++) {
            char name[MAX_STR];
            assert(scanf(" %s", name) == 1);
            find_insert(name);
        }
        for (; r > 0; r--) {
            char name[2][MAX_STR];
            animal_t *set[2];
            for (i = 0; i < 2; i++) {
                assert(scanf(" %s", name[i]) == 1);
                set[i] = find_insert(name[i]);
            }
            join_sets(set[0], set[1]);
        }
        printf("%d\n", largest_set());
    }
    return EXIT_SUCCESS;
}
