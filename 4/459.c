/* 459
 * Graph Connectivity
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE 10
#define MAX_ELEMENTS 30

typedef struct set_s {
    struct set_s *parent;
    int rank;
    char visited;
} set_t, *set_p;

set_t set[MAX_ELEMENTS];
int num_elements;

/* Initialize sets */
void initialize_sets() {
    int i;
    for (i = 0; i < num_elements; i++) {
        set[i].parent = &set[i];
        set[i].rank = 0;
        set[i].visited = 0;
    }
}

/* Get the set representative */
set_p get_set(set_p node) {
    if (node->parent == node) {
        return node;
    }
    node->parent = get_set(node->parent);
    node->rank = 1;
    return node->parent;
}

/* Join two sets */
void join_sets(set_p a, set_p b) {
    set_p sa = get_set(a), sb = get_set(b);
    if (sa == sb) {
        return;
    }
    if (sa->rank < sb->rank) {
        sa->parent = sb;
    }
    else {
        sb->parent = sa;
        sb->rank += (sb->rank == sa->rank ? 1 : 0);
    }
}

/* Main function */
int main() {
    char line[MAX_LINE];
    int tests, i, num_comp;
    assert(fgets(line, MAX_LINE, stdin) != NULL);
    tests = atoi(line);
    assert(fgets(line, MAX_LINE, stdin) != NULL && *line == '\n');
    for (; tests > 0; tests--) {
        assert(fgets(line, MAX_LINE, stdin) != NULL);
        num_elements = *line - 'A' + 1;
        initialize_sets();
        while (fgets(line, MAX_LINE, stdin) != NULL && *line != '\n') {
            join_sets(&set[line[0] - 'A'], &set[line[1] - 'A']);
        }
        for (i = 0, num_comp = 0; i < num_elements; i++) {
            set_p component = get_set(&set[i]);
            if (!component->visited) {
                component->visited = 1, num_comp++;
            }
        }
        printf("%d\n%s", num_comp, (tests > 1 ? "\n" : ""));
    }
    return 0;
}
