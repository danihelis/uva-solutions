/* 11709
 * Trust groups
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  25
#define MAX_N       1000

typedef struct node_s {
    struct node_s *edge[MAX_N];
    int num_edges;
    char name[MAX_STRING];
    int low, visited, stacked, component;
} node_t;

typedef struct {
    node_t *data[MAX_N];
    int top;
} stack_t;

node_t node[MAX_N], *reference[MAX_N];
int num_nodes;

/* Compare two node pointers by name */
int compare(const void *a, const void *b) {
    node_t *pa = *((node_t **) a), *pb = *((node_t **) b);
    return strcmp(pa->name, pb->name);
}

/* Visit a node */
void visit(node_t *node, int *index, int *component, stack_t *stack) {
    int i;
    /* Visit reachable vertices from this node */
    (*index)++;
    node->low = node->visited = *index;
    stack->data[stack->top++] = node;
    node->stacked = 1;
    for (i = 0; i < node->num_edges; i++) {
        node_t *next = node->edge[i];
        if (!next->visited) visit(next, index, component, stack);
        if (next->stacked && next->low < node->low) node->low = next->low;
    }
    /* Pop visited nodes from stack and set component */
    if (node->low == node->visited) {
        node_t *other = NULL;
        while (stack->top > 0 && other != node) {
            other = stack->data[--(stack->top)];
            other->component = *component;
            other->stacked = 0;
        }
        (*component)++;
    }
}

/* Get strong components for DAG */
int get_strong_components() {
    int i, index, num_components;
    stack_t stack;
    for (i = 0; i < num_nodes; i++) {
        node[i].visited = node[i].stacked = 0;
    }
    for (i = index = num_components = stack.top = 0; i < num_nodes; i++) {
        if (!node[i].visited) visit(&node[i], &index, &num_components, &stack);
    }
    return num_components;
}

/* Main function */
int main() {
    int num_links;
    while (scanf("%d %d", &num_nodes, &num_links) != EOF && num_nodes > 0) {
        int i;
        for (i = 0; i < num_nodes; i++) {
            node_t *n = &node[i];
            assert(scanf(" %[^\n]", n->name) != EOF);
            reference[i] = n, n->num_edges = 0;
        }
        qsort(reference, num_nodes, sizeof (node_t *), compare);
        while (num_links-- > 0) {
            node_t a, b, *pa, *pb;
            pa = &a, pb = &b;
            assert(scanf(" %[^\n] %[^\n]", a.name, b.name) != EOF);
            pa = * (node_t **) bsearch(&pa, reference, num_nodes, 
                    sizeof (node_t *), compare);
            pb = * (node_t **) bsearch(&pb, reference, num_nodes,
                    sizeof (node_t *), compare);
            pa->edge[pa->num_edges++] = pb;
        }
        printf("%d\n", get_strong_components());
    }
    return EXIT_SUCCESS;
}
