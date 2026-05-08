/* 11525
 * Permutation
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K           50010
#define MAX_MEM         (2 * MAX_K)


typedef struct node_s {
    struct node_s *subtree[2];
    int length, value;
    char is_leaf;
} node_t;

node_t nodes[MAX_MEM];
int num_nodes;
node_t *free_node;

/* Create lookup subtree for a given interval */
node_t * create_lookup_subtree(int start, int end) {
    assert(start < end);

    if (end - start == 1) {
        return &nodes[start];
    } else {
        int middle = (start + end) / 2;
        node_t *t = free_node++;

        t->subtree[0] = create_lookup_subtree(start, middle);
        t->subtree[1] = create_lookup_subtree(middle, end);
        t->is_leaf = 0;
        t->length = end - start;
        return t;
    }
}

/* Create lookup tree containing K nodes */
node_t * create_lookup_tree(int k) {
    int i;

    num_nodes = k;
    for (i = 0; i < k; i++) {
        node_t *n = &nodes[i];
        n->is_leaf = n->length = 1;
        n->value = i + 1;
    }

    free_node = &nodes[k];
    return create_lookup_subtree(0, k);
}

/* Get the N-th value from the subtree and erase it */
int get_and_remove(node_t *tree, int n) {
    assert(n < tree->length);

    tree->length--;
    if (tree->is_leaf) {
        return tree->value;
    } else if (n < tree->subtree[0]->length) {
        return get_and_remove(tree->subtree[0], n);
    } else {
        return get_and_remove(tree->subtree[1], n - tree->subtree[0]->length);
    }
}

/* Main function */
int main() {
    int k, n, num_tests;
    node_t *tree;

    assert(scanf("%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        assert(scanf("%d", &k) == 1);

        tree = create_lookup_tree(k);
        while (k-- > 0) {
            assert(scanf("%d", &n) == 1);
            printf("%d%c", get_and_remove(tree, n), k > 0 ? ' ' : '\n');
        }
    }

    return EXIT_SUCCESS;
}
