/* 11631
 * Dark roads
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES           200000
#define MAX_CONNECTIONS     200000

typedef struct {
    int a, b, dist;
} connection_t;

int set[MAX_NODES];
connection_t conn[MAX_CONNECTIONS], *p_conn[MAX_CONNECTIONS];
int num_nodes, num_conns;

/* Get set */
int get_set(int i) {
    if (set[i] == i)
        return i;
    set[i] = get_set(set[i]);
    return set[i];
}

/* Compare two connection pointes */
int compare(const void *a, const void *b) {
    connection_t *x = * (connection_t **) a, *y = * (connection_t **) b;
    return x->dist - y->dist;
}

/* Minimum spanning tree */
int mst() {
    int i, tree, cost;
    for (i = 0; i < num_nodes; i++)
        set[i] = i;
    qsort(p_conn, num_conns, sizeof (connection_t *), compare);
    for (i = 0, tree = 0, cost = 0; i < num_conns && tree < num_nodes - 1; 
            i++) {
        connection_t *con = p_conn[i];
        int set_a = get_set(con->a), set_b = get_set(con->b);
        if (set_a != set_b)
            set[set_a] = set_b, tree++, cost += con->dist;
    }
    return cost;
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_nodes, &num_conns) != EOF && num_nodes > 0) {
        int i, total_cost;
        for (i = 0, total_cost = 0; i < num_conns; i++) {
            connection_t *c = &conn[i];
            assert(scanf("%d %d %d", &c->a, &c->b, &c->dist) != EOF);
            total_cost += c->dist;
            p_conn[i] = c;
        }
        printf("%d\n", total_cost - mst());
    }
    return EXIT_SUCCESS;
}
