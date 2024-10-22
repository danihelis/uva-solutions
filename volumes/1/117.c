/**
 * 117
 * The Postal Worker Rings Once
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NODES 26
#define MAX_NAME  1024

int dist[MAX_NODES][MAX_NODES];
int degree[MAX_NODES];
int all_paths;

typedef enum {
    NOT_VISITED = 0,
    TO_BE_USED,
    USED
} status_t;


/* Find shortest path linking two nodes -- the path doesn't matter */
int shortest_path(int a, int b) {
    int best_path[MAX_NODES];
    status_t status[MAX_NODES];
    int node, shortest = -1;

    memset(status, 0, MAX_NODES * sizeof (status_t));
    best_path[a] = 0;
    status[a] = TO_BE_USED;
    node = -1;
    do {
        int i;
        shortest = -1;

        /* Select shortest node */
        for (i = 0; i < MAX_NODES; i++) {
            if (status[i] == TO_BE_USED && (shortest == -1 || best_path[i] < shortest)) {
                node = i;
                shortest = best_path[i];
            }
        }
        assert(shortest != -1);
        status[node] = USED;

        /* Update all paths */
        for (i = 0; i < MAX_NODES; i++) {
            if (dist[node][i] != -1 && status[i] != USED && 
                    (status[i] == NOT_VISITED || best_path[i] > shortest + dist[node][i])) {
                status[i] = TO_BE_USED;
                best_path[i] = shortest + dist[node][i];
            }
        }
    }
    while (node != b);
    return shortest;
}


/* Eulerian tour:
 * 1. The minimal eulerian tour is the sum of all paths plus the shortest path
 *    between two odd nodes. 
 */
int get_shortest_rewalk() {
    int start = -1, end = -1;
    int i;

    /* Determine both odd points */
    for (i = 0; i < MAX_NODES; i++) {
        if (degree[i] % 2 == 1) {
            if (start == -1) {
                start = i;
            }
            else {
                end = i;
                break;
            }
        }
    }

    return (start == -1 ? 0 : shortest_path(start, end));
}


/* Add new path to the graph */
#define TO_INDEX(c) ((c) - 'a')
void add_path(char *street) {
    int new_dist, start, end;
    new_dist = strlen(street);
    start = TO_INDEX(street[0]);
    end = TO_INDEX(street[new_dist - 1]);
    all_paths += new_dist;
    degree[start]++;
    degree[end]++;
    if (dist[start][end] == -1 || new_dist < dist[start][end]) {
        dist[start][end] = new_dist;
        dist[end][start] = new_dist;
    }
}


/* Main */
int main() {
    char street[MAX_NAME];

    while (scanf("%s", street) == 1) {
        memset(dist, 0xff, (MAX_NODES * MAX_NODES) * sizeof (int));
        memset(degree, 0, MAX_NODES * sizeof (int));
        all_paths = 0;

        while (strcmp(street, "deadend") != 0) {
            add_path(street);
            scanf("%s", street);
        }
        printf("%d\n", all_paths + get_shortest_rewalk());
    }
    return 0;
}

