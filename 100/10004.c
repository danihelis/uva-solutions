/* 10004
 * Bicoloring
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES           200
#define ADD_EDGE(v1, v2)    node[v1].link[node[v1].num_links++] = &node[v2]
#define OPP_COLOR(x)        (x == BLACK ? WHITE : BLACK)

typedef enum {
    NO_COLOR,
    BLACK, 
    WHITE
} color_t;

typedef struct node_s {
    struct node_s *link[MAX_NODES];
    int num_links;
    color_t color;
} node_t, *node_p;

node_t node[MAX_NODES];
int num_nodes;

/* Find cycle in a graph */
#define VISIT(n, c)     stack[top++] = (n); (n)->color = (c)
int cycle() {
    node_p stack[MAX_NODES];
    int i, top = 0;
    VISIT(&node[0], BLACK);
    while (top > 0) {
        node_p this = stack[--top];
        for (i = 0; i < this->num_links; i++) {
            node_p next = this->link[i];
            if (next->color == NO_COLOR) {
                VISIT(next, OPP_COLOR(this->color));
            }
            else if (next->color == this->color) {
                return 1;
            }
        }
    }
    return 0;
}

/* Main function */

int main() {
    int a, b, num_edges;
    while (scanf("%d %d", &num_nodes, &num_edges) == 2 ) {
        for (a = 0; a < num_nodes; a++) {
            node[a].num_links = 0, node[a].color = NO_COLOR;
        }
        for (; num_edges > 0; num_edges--) {
            assert(scanf("%d %d", &a, &b) != EOF);
            ADD_EDGE(a, b);
            ADD_EDGE(b, a);
        }
        printf("%sBICOLORABLE.\n", (cycle() ? "NOT " : ""));
    }
    return 0;
}
