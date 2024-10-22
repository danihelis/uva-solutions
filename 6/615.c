/* 615
 * Is It A Tree?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define UNVISITED   0
#define IN_STACK    1
#define VISITED     2

#define MAX_TABLE   99991

typedef struct node_s {
    int code, index;
    struct node_s *parent;
    char visited;
} node_t;

node_t *hash[MAX_TABLE];
node_t graph[MAX_TABLE];
int size;

/* Retrieve hashtable index */
int retrieve_index(int code) {
    int key = code % MAX_TABLE;
    int index = key;
    while (hash[index] != NULL && hash[index]->code != code) {
        index = (index + 2) % MAX_TABLE;
        assert(index != key); /* overflow */
    }
    return index;
}

/* Insert on hash */
node_t * find_or_insert(int code) {
    int index = retrieve_index(code);
    if (hash[index] != NULL)
        return hash[index];
    else {
        node_t *n = &graph[size++];
        n->code = code;
        n->index = index;
        n->parent = NULL;
        n->visited = UNVISITED;
        hash[index] = n;
        return n;
    }
}

/* Clear hash */
void clear_hash() {
    int i;
    for (i = 0; i < size; i++)
        hash[graph[i].index] = NULL;
}

/* Whether a root is reached or not (in case of cycle) */
int reach_root(node_t *n) {
    if (n->parent == NULL || n->visited == VISITED)
        return 1;
    else if (n->visited == IN_STACK)
        return 0;
    n->visited = IN_STACK;
    if (reach_root(n->parent)) {
        n->visited = VISITED;
        return 1;
    }
    return 0;
}

/* Main function */
int main() {
    int a, b, test = 0;
    memset(hash, 0, sizeof (hash));
    while (scanf("%d %d", &a, &b) == 2 && a >= 0) {
        int i, is_tree = 1;
        node_t *root = NULL;
        size = 0;
        while (a > 0) {
            node_t *na = find_or_insert(a),
                   *nb = find_or_insert(b);
            if (nb->parent != NULL) 
                is_tree = 0; /* C.2: only one parent */
            nb->parent = na;
            assert(scanf("%d %d", &a, &b) == 2);
        }
        if (size > 0 && is_tree) {
            for (i = 0; is_tree && i < size; i++)
                if (graph[i].parent == NULL) {
                    is_tree = root == NULL; /* C.1b: only one root */
                    root = &graph[i];
                }
            is_tree &= root != NULL; /* C.1a: a root exists */
            for (i = 0; is_tree && i < size; i++)
                if (graph[i].visited == UNVISITED) 
                    is_tree = reach_root(&graph[i]); /* C.3: path to root */
        }
        clear_hash();
        printf("Case %d is%s a tree.\n", ++test, is_tree ? "" : " not");
    }
    return EXIT_SUCCESS;
}
