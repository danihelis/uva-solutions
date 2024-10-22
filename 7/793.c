/* 793
 * Network Connections
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES 10000
#define MAX_STRING 50

typedef struct set_s {
    struct set_s *parent;
} set_t, *set_p;

set_t node[MAX_NODES];
int num_nodes;

/* Initialize sets */
void init_nodes() {
    int i;
    for (i = 0; i < num_nodes; i++) {
        node[i].parent = &node[i];
    }
}

/* Get representative */
set_p find(set_p set) {
    if (set != set->parent) {
        set->parent = find(set->parent);
    }
    return set->parent;
}

/* Join two sets */
void join(set_p x, set_p y) {
    set_p set_x = find(x), set_y = find(y);
    if (set_x != set_y) {
        set_x->parent = set_y;
    }
}

/* Main function */
int main() {
    int num_tests;
    char string[MAX_STRING];
    assert(fgets(string, MAX_STRING, stdin) != NULL);
    num_tests = atoi(string);
    assert(fgets(string, MAX_STRING, stdin) != NULL && *string == '\n');
    for (; num_tests > 0; num_tests--) {
        int correct = 0, queries = 0;
        assert(fgets(string, MAX_STRING, stdin) != NULL);
        num_nodes = atoi(string);
        init_nodes();
        while (fgets(string, MAX_STRING, stdin) != NULL && *string != '\n') {
            char command;
            int a, b;
            assert(sscanf(string, "%c %d %d", &command, &a, &b) == 3);
            if (command == 'c') {
                join(&node[--a], &node[--b]);
            }
            else {
                queries++, correct += (find(&node[--a]) == find(&node[--b]) ? 1 : 0);
            }
        }
        printf("%d,%d\n%s", correct, queries - correct, (num_tests > 1 ? "\n" : ""));
    }
    return 0;
}
