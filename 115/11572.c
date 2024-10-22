/* 11572
 * Unique Snowflakes
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct elem_s {
    int key, index;
    struct elem_s *next;
} elem_t;

#define MAX_HASH    99991

elem_t *hash[MAX_HASH];

/* Find an element in the hash */
elem_t * find(int key) {
    int hash_key = key % MAX_HASH;
    elem_t *node = hash[hash_key];
    while (node != NULL) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

/* Insert element in the hash */
void insert(int key, int index) {
    int hash_key = key % MAX_HASH;
    elem_t *node = (elem_t *) malloc(sizeof (elem_t));
    node->key = key, node->index = index;
    node->next = hash[hash_key];
    hash[hash_key] = node;
}

/* Clean hash */
void clean() {
    int i;
    for (i = 0; i < MAX_HASH; i++) {
        elem_t *node = hash[i];
        while (node != NULL) {
            elem_t *next = node->next;
            free(node);
            node = next;
        }
        hash[i] = NULL;
    }
}

/* Main function */
#define MAX(x,y)    ((x) > (y) ? (x) : (y))
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    memset(hash, 0, MAX_HASH * sizeof (elem_t *));
    for (; num_tests > 0; num_tests--) {
        int i, n, max, offset;
        assert(scanf("%d", &n) != EOF);
        for (i = 0, max = 0, offset = 0; i < n; i++) {
            elem_t *elem;
            int key;
            assert(scanf("%d", &key) != EOF);
            elem = find(key);
            if (elem != NULL) {
                offset = MAX(elem->index, offset);
                elem->index = i + 1;
            }
            else {
                insert(key, i + 1);
            }
            if (i - offset + 1 > max) {
                max = i - offset + 1;
            }            
        }
        printf("%d\n", max);
        if (num_tests > 1) {
            clean();
        }
    }

    return 0;
}
