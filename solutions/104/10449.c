/* 10449
 * Traffic
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       200
#define INFINITY    20000000
#define NEGATIVE    -INFINITY

typedef struct junction_s {
    struct junction_s *edge[MAX_N];
    int tax[MAX_N];
    int num_edges, busyness, earning, reached;
} junction_t;

junction_t junction[MAX_N];
int num_junctions, negative_cycle;

/* Compute earning using Bellman-Ford's */
void compute_earnings() {
    int i, k, e;
    for (i = 0; i < num_junctions; i++) {
        junction_t *j = &junction[i];
        j->earning = i == 0 ? 0 : INFINITY;
        j->reached = i == 0;
        for (e = 0; e < j->num_edges; e++) {
            junction_t *n = j->edge[e];
            int cost = (n->busyness - j->busyness);
            j->tax[e] = cost * cost * cost;
        }
    }
    for (k = 0; k < num_junctions - 1; k++) {
        for (i = 0; i < num_junctions; i++) {
            junction_t *j = &junction[i];
            for (e = 0; e < j->num_edges; e++) {
                junction_t *n = j->edge[e];
                int earning = j->tax[e] + j->earning;
                if (earning < n->earning) {
                    n->earning = earning;
                    n->reached |= j->reached;
                }
            }
        }
    }
    for (k = 0; k < num_junctions - 1; k++) {
        for (i = 0; i < num_junctions; i++) {
            junction_t *j = &junction[i];
            for (e = 0; e < j->num_edges; e++) {
                junction_t *n = j->edge[e];
                int earning = j->tax[e] + j->earning;
                if (earning < n->earning) n->earning = NEGATIVE;
            }
        }
    }
}

/* Main function */
int main() {
    int test = 0;
    int i, num_edges, num_queries;
    junction_t *j;
    while (scanf("%d", &num_junctions) == 1) {
        for (i = 0; i < num_junctions; i++) {
            j = &junction[i];
            assert(scanf("%d", &j->busyness) == 1);
            j->num_edges = 0;
        }
        assert(scanf("%d", &num_edges) == 1);
        while (num_edges-- > 0) {
            int a, b;
            assert(scanf("%d %d", &a, &b) == 2);
            j = &junction[--a];
            j->edge[j->num_edges++] = &junction[--b];
        }
        compute_earnings();
        assert(scanf("%d", &num_queries) == 1);
        printf("Set #%d\n", ++test);
        while (num_queries-- > 0) {
            int a;
            assert(scanf("%d", &a) == 1);
            j = &junction[--a];
            if (j->earning < 3 || !j->reached) printf("?\n");
            else printf("%d\n", j->earning);
        }
    }
    return EXIT_SUCCESS;
}
