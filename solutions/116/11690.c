/* 11690
 * Money Matters
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000

typedef struct node_s {
    int value, total, included;
    struct node_s *set;
} node_t;

node_t node[MAX_N], *set[MAX_N];
int num_nodes, num_sets;

/* Get set */
node_t * get_set(node_t *s) {
    if (s->set != s)
        s->set = get_set(s->set);
    return s->set;
}

/* Join sets */
void join_sets(node_t *a, node_t *b) {
    node_t *s = get_set(a);
    s->set = get_set(b);
}

/* Main function */
int main() {
    int i, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int j, possible, num_edges;
        assert(scanf("%d %d", &num_nodes, &num_edges) == 2);
        for (i = 0; i < num_nodes; i++) {
            node_t *n = &node[i];
            assert(scanf("%d", &n->value) == 1);
            n->total = n->included = 0, n->set = n;
        }
        while (num_edges-- > 0) {
            assert(scanf("%d %d", &i, &j) == 2);
            join_sets(&node[i], &node[j]);
        }
        for (i = 0, num_sets = 0; i < num_nodes; i++) {
            node_t *s = get_set(node[i].set);
            if (!s->included)
                set[num_sets++] = s, s->included = 1;
            s->total += node[i].value;
        }
        for (i = 0, possible = 1; possible && i < num_sets; i++)
            possible = set[i]->total == 0;
        puts(possible ? "POSSIBLE" : "IMPOSSIBLE");
    }
    return EXIT_SUCCESS;
}
