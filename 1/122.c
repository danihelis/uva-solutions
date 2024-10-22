/**
 * 122
 * Trees on the Level
 * by Daniel Donadon
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TREE 300
#define MAX_LABEL (MAX_TREE + 1)
#define MAX_LINE 2048

typedef struct node_t {
    int value;
    char path[MAX_LABEL];
    struct node_t *left, *right;
    int reached;
} node_t;

node_t forest[MAX_TREE];
node_t *root;
int elements, reachable;


/* Get a node from a given chose path, if existent */
node_t *get_node_to_path(char *original, char dir) {
    char path[MAX_LABEL];
    int path_length = strlen(original);
    int i;

    strcpy(path, original);
    path[path_length++] = dir;
    path[path_length] = '\0';
    for (i = 0; i < elements; i++) {
        if (strcmp(path, forest[i].path) == 0) {
            return &forest[i];
        }
    }
    return NULL;
}


/* Link a new node to the tree.
 * A node is said to be reachable whenever someone links it. */
void link_node(node_t *node) {
    char path[MAX_LABEL], dir;
    int path_length = strlen(node->path);
    node_t *other;
    
    /* Link to previous */
    if (path_length == 0) {
        root = node;
        reachable++;
    }
    else {
        strcpy(path, node->path);
        dir = path[path_length - 1];
        path[path_length - 1] = '\0';
        other = get_node_to_path(path, '\0');
        if (other != NULL) {
            reachable++;
            switch (dir) {
                case 'L':
                    other->left = node;
                    break;
                case 'R':
                    other->right = node;
                    break;
            }
        }
    }

    /* Link to following */
    strcpy(path, node->path);
    other = get_node_to_path(path, 'L');
    if (other != NULL) {
        node->left = other;
        reachable++;
    }
    other = get_node_to_path(path, 'R');
    if (other != NULL) {
        node->right = other;
        reachable++;
    }
}


/* Macros for easy reading! */
#define REMOVE_ENDLINE(c, k) \
    do { \
        char *c_remove_; \
        while ((c_remove_ = strchr(c, k)) != NULL) { \
            *c_remove_ = '\0'; \
        } \
    } while (0)

#define READ_SPACE(c) \
    do { \
        while (*c == ' ') { \
            c++; \
        } \
    } while (0)

#define SKIP_CHAR(c, k) assert(*c == k); c++

#define READ_NUMBER(n, c) \
    do { \
        n = 0; \
        while (*c >= '0' && *c <= '9') { \
            n *= 10; \
            n += *c - '0'; \
            c++; \
        } \
    } while (0)

#define READ_DIRECTIONS(s, c) \
    do { \
        char *c_offset_ = c; \
        while (*c == 'L' || *c == 'R') { \
            s[c - c_offset_] = *c; \
            c++; \
        } \
        s[c - c_offset_] = '\0'; \
    } while (0)


/* Read a set of nodes and link them */
int read_nodes() {
    char line[MAX_LINE], *c = NULL;
    int finished;

    elements = 0;
    reachable = 0;
    finished = 0;
    root = NULL;
    while (!finished && (c = fgets(line, MAX_LINE, stdin)) != NULL) {
        REMOVE_ENDLINE(c, '\n');
        REMOVE_ENDLINE(c, '\r');
        while (*c != '\0') {
            READ_SPACE(c);
            SKIP_CHAR(c, '(');
            if (*c == ')') {
                 /* End of tree description */
                finished = 1;
                break;
            }
            forest[elements].left = NULL;
            forest[elements].right = NULL;
            READ_NUMBER(forest[elements].value, c);
            SKIP_CHAR(c, ',');
            READ_DIRECTIONS(forest[elements].path, c);
            SKIP_CHAR(c, ')');
            if (get_node_to_path(forest[elements].path, '\0') != NULL) {
                /* A node cannot be repeated */
                reachable = - MAX_TREE;
            }
            link_node(&forest[elements]);
            elements++;
            READ_SPACE(c);
        }
    }
    return c != NULL;
}


/* Visit the three by level (breadth-first) */
void breadth_visit_tree() {
    node_t *queue[MAX_TREE];
    int size_queue, i, first_print = 1;

    if (root == NULL) {
        return;
    }
    
    queue[0] = root;
    size_queue = 1;
    i = 0;
    while (i < size_queue) {
        node_t *current = queue[i++];
        if (current == NULL) {
            continue;
        }
        if (first_print) {
            first_print = 0;
        }
        else {
            printf(" ");
        }
        printf("%d", current->value);
        if (current->left != NULL) {
            queue[size_queue++] = current->left;
        }
        if (current->right != NULL) {
            queue[size_queue++] = current->right;
        }
    }
}


/* Main */
int main() {

    while (read_nodes()) {
        if (elements != reachable) {
            printf("not complete");
        }
        else {
            breadth_visit_tree();
        }
        printf("\n");
    }
    return 0;
}

