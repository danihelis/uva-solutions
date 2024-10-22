/* 599
 * The Forrest for the Trees
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   26
#define MAX_STRING  (MAX_NODES * 4)
#define INDEX(x)    ((x) - 'A')

typedef struct node_s {
    struct node_s *set;
    int count;
} node_t;

node_t node[MAX_NODES];

/* Get the set of a node */
node_t * get_set(node_t *n) {
    if (n->set == n)
        return n;
    n->set = get_set(n->set);
    return n->set;
}

/* Join two sets into one */
void join(node_t *set1, node_t *set2) {
    node_t *set = get_set(set1);
    set->set = get_set(set2);
}

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char line[MAX_STRING], *p;
    int tests;
    assert(READ(line));
    for (tests = atoi(line); tests > 0; tests--) {
        int i, trees, acorns;
        for (i = 0; i < MAX_NODES; i++) {
            node[i].set = &node[i];
            node[i].count = 0;
        }
        while (READ(line) && line[0] != '*') {
            char i1 = 0, i2 = 0;
            for (p = line; *p != 0 && i2 == 0; p++) {
                if (isalpha(*p)) 
                    (i1 == 0 ? (void) (i1 = *p) : (void) (i2 = *p));
            }
            assert(i1 != 0 && i2 != 0);
            join(&node[INDEX(i1)], &node[INDEX(i2)]);
        }
        assert(READ(line));
        for (p = line; *p != 0; p++) {
            if (isalpha(*p)) {
                node_t *set = get_set(&node[INDEX(*p)]);
                set->count++;
            }
        }
        for (trees = 0, acorns = 0, i = 0; i < MAX_NODES; i++) {
            if (node[i].count == 1)
                acorns++;
            else if (node[i].count > 1)
                trees++;
        }
        printf("There are %d tree(s) and %d acorn(s).\n", trees, acorns);
    }
    return 0;
}
