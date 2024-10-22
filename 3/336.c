/* 336
 * A Node Too Far
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES 50
#define INFINITY (MAX_NODES + 1)

typedef struct node_s {
    int id;
    struct node_s *link[MAX_NODES];
    int num_links;
    int hops;
} node_t, *node_p;

node_t node[MAX_NODES];
node_p index[MAX_NODES];
int num_nodes;

/* Get a node by id using binary search */
node_p get_node(int id, char insert) {
    int start, end, middle;
    start = 0, end = num_nodes;
    while (start < end) {
        middle = (start + end) / 2;
        if (index[middle]->id == id) {
            return index[middle];
        }
        else if (index[middle]->id < id) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    if (!insert) {
        return NULL;
    }
    node[num_nodes].id = id;
    node[num_nodes].num_links = 0;
    for (end = num_nodes; end > start; end--) {
        index[end] = index[end - 1];
    }
    index[start] = &node[num_nodes];
    num_nodes++;
    return index[start];
}

/* Return the number of nodes reached from start by traversing at most k nodes */
int nodes_reached(int start_id, int max_hops) {
    node_p queue[MAX_NODES];
    int i, front, end, count;
    for (i = 0; i < num_nodes; i++) {
        node[i].hops = INFINITY;
    }
    queue[0] = get_node(start_id, 0), front = 0, end = 1, count = 0;
    if (queue[0] == NULL) {
        return 0;
    }
    queue[0]->hops = 0;
    while (front < end) {
        node_p current = queue[front++];
        if (current->hops > max_hops) {
            break;
        }
        count++;
        for (i = 0; i < current->num_links; i++) {
            node_p neighbour = current->link[i];
            if (neighbour->hops == INFINITY) {
                queue[end++] = neighbour;
            }
            if (neighbour->hops > current->hops + 1) {
                neighbour->hops = current->hops + 1;
            }
        }
    }
    return count;    
}

/* Main function */
int main() {
    int i, num_pairs, query = 1;
    while (scanf("%d", &num_pairs) != EOF) {
        int a, b;
        if (num_pairs == 0) {
            break;
        }
        for (i = 0, num_nodes = 0; i < num_pairs; i++) {
            node_p na, nb;
            assert(scanf(" %d %d", &a, &b) != EOF);
            na = get_node(a, 1);
            nb = get_node(b, 1);
            na->link[na->num_links++] = nb;
            nb->link[nb->num_links++] = na;
        }
        while (scanf(" %d %d", &a, &b) != EOF) {
            if (a == 0 && b == 0) {
                break;
            }
            printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n",
                    query++, num_nodes - nodes_reached(a, b), a, b);
        }
    }
    return 0;
}
