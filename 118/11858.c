/* 11858
 * Frosh Week
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ORDER       16
#define COUNT(x)    ((x) == NULL ? 0 : (x)->count)

typedef struct node_s node_t;

typedef struct {
    long value;
    node_t *child;
} seminode_t;

struct node_s {
    seminode_t semi[ORDER + 1];
    node_t *last_child;
    int size, count;
};

node_t *root;
seminode_t seminode;

/* Insert (if not present) and split */
void insert_and_split(node_t *node, long value, seminode_t **up) {
    if (node == NULL) {
        *up = &seminode;
        seminode.value = value, seminode.child = NULL;
    }
    else {
        int i, pos;
        node->count++;
        for (pos = 0; pos < node->size; pos++)
            if (value > node->semi[pos].value) {
                insert_and_split(node->semi[pos].child, value, up);
                break;
            }
        if (pos == node->size)
            insert_and_split(node->last_child, value, up);
        if (*up != NULL) {
            for (i = node->size; i > pos; i--)
                node->semi[i] = node->semi[i - 1];
            node->semi[pos] = **up;
            node->size++;
            if (node->size <= ORDER)
                *up = NULL;
            else {
                int middle = ORDER / 2;
                *up = &seminode;
                seminode.child = (node_t *) malloc(sizeof (node_t));
                seminode.value = node->semi[middle].value;
                seminode.child->last_child = node->semi[middle].child;
                seminode.child->count = COUNT(seminode.child->last_child);
                node->count = COUNT(node->last_child);
                for (i = 0; i < middle; i++) {
                    seminode.child->semi[i] = node->semi[i];
                    seminode.child->count += 1 + COUNT(node->semi[i].child);
                    node->semi[i] = node->semi[i + middle + 1];
                    node->count += 1 + COUNT(node->semi[i].child);
                }
                seminode.child->size = node->size = middle;
            }
        }
    }
}

/* Insert (if not present) at root */
void insert(long value) {
    seminode_t *up;
    insert_and_split(root, value, &up);
    if (up != NULL) {
        node_t *new_root = (node_t *) malloc(sizeof (node_t));
        new_root->last_child = root;
        new_root->semi[0] = *up;
        new_root->size = 1;
        new_root->count = 1 + COUNT(root) + COUNT(up->child);
        root = new_root;
    }
}

/* Get index */
int get_index(node_t *node, long value) {
    int pos, index;
    assert(node != NULL);
    for (pos = index = 0; pos < node->size; pos++) {
        if (value == node->semi[pos].value)
            return index + COUNT(node->semi[pos].child);
        else if (value > node->semi[pos].value)
            return index + get_index(node->semi[pos].child, value);
        index += 1 + COUNT(node->semi[pos].child);
    }
    return index + get_index(node->last_child, value);    
}

/* Deallocate tree */
void deallocate(node_t *node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->size; i++)
            deallocate(node->semi[i].child);
        deallocate(node->last_child);
        free(node);
    }
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int i;
        long v, swaps;
        root = NULL;
        for (i = swaps = 0; i < n; i++) {
            assert(scanf("%ld", &v) == 1);
            insert(v);
            swaps += get_index(root, v);
        }
        printf("%ld\n", swaps);
        deallocate(root);
    }
    return EXIT_SUCCESS;
}
