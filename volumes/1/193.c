/* 193
 * Graph Coloring
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES   100
#define NO_COLOR    -1
#define BLACK       -10

typedef struct {
    int link[MAX_NODES];
    int num_links, colour;
} node_t, *node_p;

node_t node[MAX_NODES];
int num_nodes;
int best_black[MAX_NODES], maximum;

/* Attempt to colour nodes in black */
void colourize(int start, int total) {
    static int solution[MAX_NODES];
    int i, j;
    for (i = start; i < num_nodes; i++) {
        if (node[i].colour == NO_COLOR) {
            node[i].colour = BLACK;
            for (j = 0; j < node[i].num_links; j++) {
                node_p next = &node[node[i].link[j]];
                assert(next->colour != BLACK);
                if (next->colour == NO_COLOR) {
                    next->colour = i;
                }
            }
            solution[total] = i;
            colourize(i + 1, total + 1);
            node[i].colour = NO_COLOR;
            for (j = 0; j < node[i].num_links; j++) {
                node_p next = &node[node[i].link[j]];
                if (next->colour == i) {
                    next->colour = NO_COLOR;
                }
            }
        }
    }
    if (total > maximum) {
        memcpy(best_black, solution, total * sizeof (int));
        maximum = total;
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_links;
        assert(scanf("%d %d", &num_nodes, &num_links) != EOF);
        for (i = 0; i < num_nodes; i++) {
            node[i].colour = NO_COLOR;
            node[i].num_links = 0;
        }
        for (i = 0; i < num_links; i++) {
            int a, b;
            assert(scanf("%d %d", &a, &b) != EOF);
            a--, b--;
            if (a > b) {
                int t = a;
                a = b;
                b = t;
            }
            node[a].link[node[a].num_links++] = b;            
        }
        maximum = 0;
        colourize(0, 0);
        printf("%d\n", maximum);
        for (i = 0; i < maximum; i++) {
            printf("%d%c", best_black[i] + 1, (i < maximum - 1 ? ' ' : '\n'));
        }
    }
    return 0;
}
