/* 12356
 * Army Buddies
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NOBODY      -1
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

typedef struct node_s {
    struct node_s *left, *right;
    int start, middle, end;
    char all_dead;
} node_t, *node_p;

/* Build segment tree */
node_p build_tree(int start, int end) {
    node_p root = (node_p) malloc(sizeof (node_t));
    root->start = start;
    root->end = end;
    root->middle = (start + end) / 2;
    root->all_dead = 0;
    root->left = (end - start == 1) ? NULL : build_tree(start, root->middle);
    root->right = (end - start == 1) ? NULL : build_tree(root->middle, end);
    return root;
}

/* Delete segment tree */
void delete(node_p root) {
    if (root->left != NULL) {
        delete(root->left);
        delete(root->right);
    }
    free(root);
}

/* Mark dead */
void mark_dead(node_p root, int start, int end) {
    assert(start >= root->start && end <= root->end);
    if (root->all_dead || (start == root->start && end == root->end)) {
        root->all_dead = 1;
    }
    else {
        if (start < root->middle) {
            mark_dead(root->left, start, MIN(end, root->middle));
        }
        if (end > root->middle) {
            mark_dead(root->right, MAX(start, root->middle), end);
        }
        root->all_dead = root->left->all_dead && root->right->all_dead;
    }
}

/* Get left buddy */
int get_leftmost(node_p root, int index) {
    if (root->all_dead || index <= root->start) {
        return NOBODY;
    }
    else if (root->left == NULL) {
        return root->start;
    }
    else {
        int leftmost = get_leftmost(root->right, index);
        return leftmost != NOBODY ? leftmost :
                get_leftmost(root->left, MIN(index, root->middle));
    }
}

/* Get right buddy */
int get_rightmost(node_p root, int index) {
    if (root->all_dead || index >= root->end) {
        return NOBODY;
    }
    else if (root->left == NULL) {
        return root->start;
    }
    else {
        int rightmost = get_rightmost(root->left, index);
        return rightmost != NOBODY ? rightmost :
                get_rightmost(root->right, MAX(index, root->middle));
    }
}

/* Main function */
int main() {
    node_p tree = NULL;
    int n, b;
    while (scanf("%d %d", &n, &b) != EOF && n > 0) {
        if (tree != NULL) {
            delete(tree);
        }
        tree = build_tree(1, n + 1);
        for (; b > 0; b--) {
            int start, end, k;
            assert(scanf("%d %d", &start, &end) != EOF);
            mark_dead(tree, start, end + 1);
            for (k = 0; k < 2; k++) {
                int pos = k == 0 ? get_leftmost(tree, start) : get_rightmost(tree, end + 1);
                (pos == NOBODY ? printf("*") : printf("%d", pos));
                (k == 0 ? printf(" ") : printf("\n"));
            }
        }
        printf("-\n");
    }
    return 0;
}
