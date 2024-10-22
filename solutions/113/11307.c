/* 11307
 * Alternative Arborescence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    10000
#define MAX_STRING      (MAX_VERTICES * 5)
#define INCREASE_SIZE   10
#define MAX_COLOURS     10
#define MIN(x,y)        ((x) < (y) ? (x) : (y))

typedef struct vertex_s {
    struct vertex_s **child, *parent;
    int num_children, max_children;
    int sum[MAX_COLOURS];
    char visited;
} vertex_t, *vertex_p;

vertex_t vertex[MAX_VERTICES];
int num_vertices;

/* Allocate space for children */
vertex_p * get_child_pointer(vertex_p root, int index) {
    if (index >= root->max_children) {
        root->max_children += INCREASE_SIZE;
        assert(index < root->max_children);
        root->child = (vertex_p *) realloc(root->child, root->max_children * sizeof (vertex_p));
    }
    return &root->child[index];
}

/* Deallocate children */
void free_children(vertex_p root) {
    if (root->max_children > 0) {
        assert(root->child != NULL);
        free(root->child);
    }
}

/* Get the minimal sum using any colour other than the one specified */
int get_any_but_this(vertex_p root, int colour) {
    int i, minimum = -1;
    for (i = 0; i < MAX_COLOURS; i++) {
        if (i != colour && (minimum == -1 || root->sum[i] < minimum)) {
            minimum = root->sum[i];
        }
    }
    return minimum;
}

/* Calculate minimal sum of subtrees */
void compute_minimal_sum(vertex_p root) {
    int i, k;
    assert(!root->visited);
    root->visited = 1;
    for (k = 0; k < MAX_COLOURS; k++) {
        root->sum[k] = (k + 1);
        for (i = 0; i < root->num_children; i++) {
            vertex_p child = root->child[i];
            if (k == 0) {
                compute_minimal_sum(child);
            }
            root->sum[k] += get_any_but_this(child, k);
        }
    }
}

/* Main function */
int main() {
    char line[MAX_STRING];
    while (fgets(line, MAX_STRING, stdin) != NULL) {
        int i;
        vertex_p root;
        num_vertices = atoi(line);
        if (num_vertices == 0) {
            break;
        }
        
        memset(vertex, 0, num_vertices * sizeof (vertex_t));
        for (i = 0; i < num_vertices; i++) {
            char *start;
            int index;
            vertex_p v, *c;
            assert(fgets(line, MAX_STRING, stdin) != NULL);
            start = strchr(line, ':');
            *start = 0;
            index = atoi(line);
            assert(index < num_vertices);
            v = &vertex[index];
            while (*start != '\n') {
                while (!isdigit(*start) && *start != '\n') {
                    start++;
                }
                if (*start == '\n') {
                    break;
                }                
                index = 0;
                while (isdigit(*start)) {
                    index = index * 10 + (*start - '0');
                    start++;
                }
                assert(index < num_vertices);
                c = get_child_pointer(v, v->num_children);
                *c = &vertex[index];
                assert((*c)->parent == NULL);
                (*c)->parent = v;
                v->num_children++;
            }
        }
        assert(fgets(line, MAX_STRING, stdin) != NULL && line[0] == '\n');

        for (i = 0, root = NULL; i < num_vertices && root == NULL; i++) {
            if (vertex[i].parent == NULL) {
                root = &vertex[i];
            }
        }
        assert(root != NULL);
        compute_minimal_sum(root);
        printf("%d\n", get_any_but_this(root, MAX_COLOURS));

        for (i = 0; i < num_vertices; i++) {
            free_children(&vertex[i]);
        }
    }
    return 0;
}
