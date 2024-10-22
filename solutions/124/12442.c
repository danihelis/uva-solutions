/* 12442
 * Forwarding Emails
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   50000

typedef struct node_s {
    struct node_s *next;
    int reach, low;
} node_t;

node_t nodes[MAX_N];
int num_nodes;

/* Visit a node */
int visit_node(node_t *node, int *low) {
    node_t *next = node->next;
    *low += 1;
    node->low = *low;
    if (next->low > 0) {
        if (next->reach > 0)
            node->reach = next->reach + 1;
        else {
            *low = next->low;
            node->reach = node->low - next->low + 1;
        }
    }
    else {
        node->reach = visit_node(next, low);
        if (*low > node->low)
            node->reach++;
    }
    return node->reach;
}

/* Return candidate that yields the greatest cycle length */
int find_greatest_cycle() {
    int i, best;
    for (i = 0; i < num_nodes; i++)
        nodes[i].reach = nodes[i].low = 0;
    for (i = 0, best = 0; i < num_nodes; i++)
        if (nodes[i].low == 0) {
            int cycle, low = 0;
            cycle = visit_node(&nodes[i], &low);
            if (cycle > nodes[best].reach)
                best = i;
        }
    return best;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, k, e;
        assert(scanf("%d", &num_nodes) != EOF);
        for (i = 0; i < num_nodes; i++) {
            assert(scanf("%d %d", &k, &e) != EOF);
            nodes[k - 1].next = &nodes[e - 1];
        }
        printf("Case %d: %d\n", test, find_greatest_cycle() + 1);
    }
    return EXIT_SUCCESS;
}
