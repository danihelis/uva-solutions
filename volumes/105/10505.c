/* 10505
 * Montesco vs Capuleto
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       200
#define NEUTRAL     0
#define BLACK       1
#define WHITE       2
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

typedef struct node_s {
    struct node_s *edge[MAX_N];
    int num_edges, color, visited, invited;
} node_t;

node_t node[MAX_N];
int num_nodes;

/* Count number of white and black nodes */
int count_colors(node_t *n, int *white, int *black) {
    int i, valid;
    if (n->color == NEUTRAL) n->color = WHITE;
    if (n->color == WHITE) (*white)++;
    else (*black)++;
    n->visited = 1;
    for (i = 0, valid = 1; i < n->num_edges; i++) {
        node_t *p = n->edge[i];
        valid &= p->color != n->color;
        if (p->visited) continue;
        if (p->color == NEUTRAL) p->color = n->color == WHITE ? BLACK : WHITE;
        valid &= count_colors(p, white, black);
    }
    return valid;
}

/* Get maximum number of invitations */
int get_max_invitations() {
    int i, white, black, total;
    for (i = total = 0; i < num_nodes; i++) {
        node_t *n = &node[i];
        if (n->visited) continue;
        white = black = 0;
        if (count_colors(n, &white, &black)) total += MAX(white, black);
    }
    return total;
}

/* Read graph */
void read_graph() {
    int i, k, v;
    assert(scanf("%d", &num_nodes) == 1);
    for (i = 0; i < num_nodes; i++) {
        node_t *n = &node[i];
        n->num_edges = n->visited = 0, n->color = NEUTRAL;
    }
    for (i = 0; i < num_nodes; i++) {
        node_t *p, *n = &node[i];
        assert(scanf("%d", &k) == 1);
        while (k-- > 0) {
            assert(scanf("%d", &v) == 1);
            if (v > num_nodes) continue;
            p = &node[v - 1];
            n->edge[n->num_edges++] = p;
            p->edge[p->num_edges++] = n;
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        read_graph();
        printf("%d\n", get_max_invitations());
    }
    return EXIT_SUCCESS;
}
