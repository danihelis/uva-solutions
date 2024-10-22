/* 11286
 * Conformity
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_VALUES  5
#define ORDER       16
#define MAX_KEYS    10000

typedef struct {
    int value[NUM_VALUES];
    int count;
} key_t;

typedef struct node_s node_t;

typedef struct {
    key_t *key;
    node_t *child;
} seminode_t;
const seminode_t NULL_SEMINODE = {NULL, NULL};

struct node_s {
    seminode_t semi[ORDER + 1];
    node_t *last_child;
    int used;
};

node_t *root;
key_t key[MAX_KEYS];

/* Compare two integers */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compare two keys */
int compare(key_t *a, key_t *b) {
    int i;
    for (i = 0; i < NUM_VALUES; i++) {
        if (a->value[i] != b->value[i]) {
            return a->value[i] - b->value[i];
        }
    }
    return 0;
}

/* Insert (if not present) and split */
seminode_t insert_and_split(node_t *node, key_t *key) {
    seminode_t up, semi;
    int i, pos;
    if (node == NULL) {
        semi.key = key, semi.child = NULL;
        key->count = 1;
        return semi;
    }
    for (pos = 0; pos < node->used; pos++) {
        int comp = compare(key, node->semi[pos].key);
        if (comp == 0) {
            node->semi[pos].key->count++;
            return NULL_SEMINODE;
        }
        else if (comp < 0) {
            up = insert_and_split(node->semi[pos].child, key);
            break;
        }
    }
    if (pos == node->used) {
        up = insert_and_split(node->last_child, key);
    }
    if (up.key != NULL) {
        for (i = node->used; i > pos; i--) {
            node->semi[i] = node->semi[i - 1];
        }
        node->semi[pos] = up;
        node->used++;
        if (node->used <= ORDER) {
            up = NULL_SEMINODE;
        }
        else {
            int middle = ORDER / 2;
            up.child = (node_t *) malloc(sizeof (node_t));
            up.key = node->semi[middle].key;
            up.child->last_child = node->semi[middle].child;
            for (i = 0; i < middle; i++) {
                up.child->semi[i] = node->semi[i];
                node->semi[i] = node->semi[i + middle + 1];
            }
            up.child->used = node->used = middle;
        }
    }
    return up;
}

/* Insert (if not present) at root */
void insert(key_t *key) {
    seminode_t up = insert_and_split(root, key);
    if (up.key != NULL) {
        node_t *new_root = (node_t *) malloc(sizeof (node_t));
        new_root->last_child = root;
        new_root->semi[0] = up;
        new_root->used = 1;
        root = new_root;
    }
}

/* Deallocate tree */
void deallocate(node_t *node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->used; i++) {
            deallocate(node->semi[i].child);
        }
        deallocate(node->last_child);
        free(node);
    }
}

/* Main function */
int main() {
    int num_keys;
    root = NULL;
    while (scanf("%d", &num_keys) != EOF && num_keys > 0) {
        int i, k, max, sum;
        deallocate(root);
        root = NULL;
        for (i = 0; i < num_keys; i++) {
            for (k = 0; k < NUM_VALUES; k++) {
                assert(scanf("%d", &key[i].value[k]) != EOF);
            }
            qsort(key[i].value, NUM_VALUES, sizeof (int), compare_int);
            key[i].count = 0;
            insert(&key[i]);
        }
        for (i = 0, max = 0; i < num_keys; i++) {
            max = key[i].count > max ? key[i].count : max;
        }
        for (i = 0, sum = 0; i < num_keys; i++) {
            sum += key[i].count == max ? key[i].count : 0;
        }
        printf("%d\n", sum);
    }
    return 0;
}
