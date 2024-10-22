/* 12086
 * Potentiometers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       200000
#define MAX_STRING  5
#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

typedef struct node_s {
    struct node_s *left, *right;
    int start, middle, end, value;
} node_t;

/* Build segment tree */
node_t * build_tree(int input[], int start, int end) {
    node_t *n = (node_t *) malloc(sizeof (node_t));
    n->start = start, n->end = end, n->middle = (start + end) / 2;
    if (start == end - 1) {
        n->value = input[start];
        n->left = n->right = NULL;
    }
    else {
        n->left = build_tree(input, start, n->middle);
        n->right = build_tree(input, n->middle, end);
        n->value = n->left->value + n->right->value;
    }
    return n;
}

/* Query segment tree */
int query(node_t *node, int start, int end) {
    assert(start >= node->start && start < node->end &&
            end > node->start && end <= node->end);
    if (node->start == start && node->end == end)
        return node->value;
    else {
        int left, right;
        left = start < node->middle ? 
            query(node->left, start, MIN(end, node->middle)) : 0;
        right = end > node->middle ? 
            query(node->right, MAX(start, node->middle), end) : 0;
        return left + right;
    }
}

/* Update segment tree */
void update(node_t *node, int pos, int value) {
    assert(pos >= node->start && pos < node->end);
    if (node->left == NULL)
        node->value = value;
    else {
        update(pos < node->middle ? node->left : node->right, pos, value);
        node->value = node->left->value + node->right->value;
    }
}

/* Free tree */
void free_tree(node_t *node) {
    if (node->left != NULL)
        free_tree(node->left), free_tree(node->right);
    free(node);
}

/* Main function */
int main() {
    int n, input[MAX_N], test = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        node_t *tree;
        char command[MAX_STRING];
        int i, a, b;
        for (i = 0; i < n; i++)
            assert(scanf("%d", &input[i]) == 1);
        tree = build_tree(input, 0, n);

        printf("%s", test == 0 ? "" : "\n");
        printf("Case %d:\n", ++test);
        while (scanf(" %s", command) == 1 && command[0] != 'E') {
            assert(scanf("%d %d", &a, &b) != EOF);
            if (command[0] == 'M')
                printf("%d\n", query(tree, a - 1, b));
            else
                update(tree, a - 1, b);
        }
        free_tree(tree);
    }
    return EXIT_SUCCESS;
}
