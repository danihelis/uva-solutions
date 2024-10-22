/* 10842
 * Traffic Flow
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES       100
#define MAX_ROADS       10000

typedef struct node_s {
    struct node_s *set;
} node_t;

typedef struct {
    node_t *a, *b;
    int cost;
} road_t;

node_t node[MAX_NODES];
road_t road[MAX_ROADS];
int num_nodes, num_roads;

/* Get set from node */
node_t * get_set(node_t *n) {
    if (n->set != n)
        n->set = get_set(n->set);
    return n->set;
}

/* Join two sets of nodes */
void join_sets(node_t *a, node_t *b) {
    node_t *set = get_set(a);
    set->set = get_set(b);
}

/* Compare two roads by cost */
int compare_road(const void *a, const void *b) {
    return ((road_t *) b)->cost - ((road_t *) a)->cost;
}

/* Compute the MST and return the lowest road cost */
int lowest_mst() {
    int i, joined, last_cost;
    for (i = 0; i < num_nodes; i++)
        node[i].set = &node[i];
    qsort(road, num_roads, sizeof (road_t), compare_road);
    for (i = joined = last_cost = 0; i < num_roads && joined < num_nodes - 1; i++) {
        road_t *r = &road[i];
        if (get_set(r->a) != get_set(r->b)) {
            join_sets(r->a, r->b);
            last_cost = r->cost;
            joined++;
        }
    }
    return last_cost;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i;
        assert(scanf("%d %d", &num_nodes, &num_roads) == 2);
        for (i = 0; i < num_roads; i++) {
            int a, b;
            road_t *r = &road[i];
            assert(scanf("%d %d %d", &a, &b, &r->cost) == 3);
            r->a = &node[a], r->b = &node[b];
        }
        printf("Case #%d: %d\n", test, lowest_mst());
    }
    return EXIT_SUCCESS;
}
