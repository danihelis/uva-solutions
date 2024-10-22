/* 11838
 * Come and Go
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   2000

typedef struct {
    int edge[MAX_NODES];
    int num_edges, low, visited, in_stack;
} node_t;

typedef struct {
    node_t *data[MAX_NODES];
    int top;
} stack_t;

node_t nodes[MAX_NODES];
int num_nodes;
stack_t stack;

/* Find a single strong component */
int find_single_strong_component(node_t *node, stack_t *stack, int *count, 
        int *total) {
    int i;
    (*count)++;
    node->low = *count;
    node->visited = *count;
    node->in_stack = 1;
    stack->data[stack->top++] = node;
    for (i = 0; i < node->num_edges; i++) {
        node_t *next = &nodes[node->edge[i]];
        if (!next->visited)
            if (!find_single_strong_component(next, stack, count, total))
                return 0;
        if (next->in_stack && next->low < node->low)
            node->low = next->low;
    }
    if (node->low == node->visited) {
        while (stack->top > 0) {
            node_t *pop = stack->data[--stack->top];
            pop->in_stack = 0;
            if (pop == node)
                break;
        }
        (*total)++;
    }
    return *total <= 1;
}

/* Determine if all nodes are connected */
int is_all_connected() {
    stack_t stack;
    int i, count = 0, total = 0, all_connected;
    stack.top = 0;
    for (i = 0; i < num_nodes; i++)
        nodes[i].visited = 0, nodes[i].in_stack = 0;
    all_connected = find_single_strong_component(&nodes[0], &stack, &count,
            &total) && count == num_nodes;
    return all_connected;    
}

/* Main function */
int main() {
    int i, num_cons;
    while (scanf("%d %d", &num_nodes, &num_cons) != EOF && num_nodes > 0) {
        for (i = 0; i < num_nodes; i++)
            nodes[i].num_edges = 0;
        for (; num_cons > 0; num_cons--) {
            int a, b, mode;
            assert(scanf("%d %d %d", &a, &b, &mode) != EOF);
            a--, b--;
            nodes[a].edge[nodes[a].num_edges++] = b;
            if (mode == 2)
                nodes[b].edge[nodes[b].num_edges++] = a;
        }
        printf("%d\n", is_all_connected() ? 1 : 0);
    }
    return EXIT_SUCCESS;
}
