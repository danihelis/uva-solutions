/* 10746
 * Crime Wave - The Sequel
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20
#define MAX_GRAPH   (MAX_N * 2)
#define INFINITY    1e37
#define EPSILON     1e-4

typedef enum {
    BANK,
    POLICE,
    SINK
} type_t;

typedef struct {
    double distance[MAX_N];
    int police;
} bank_t;

typedef struct {
    double distance;
    int bank;
} police_t;

bank_t bank[MAX_N];
police_t police[MAX_N];
int n, m;

typedef struct {
    int visited, prior, index;
    type_t type;
    double distance;
} vertex_t;

/* Find Bellman-Ford's shortest path and augment the min cost max flow */
void augment_shortest_path_bellman_ford() {
    vertex_t vertex[MAX_GRAPH + 1];
    int current, i, j, k, dim, size;

    /* Init */
    for (k = 0, size = 0; k < 2; k++) {
        for (i = 0, dim = k ? m : n; i < dim; i++, size++) {
            vertex[size].prior = -1;
            vertex[size].distance = (k || bank[i].police != -1) ?
                    INFINITY : 0;
            vertex[size].type = k ? POLICE : BANK;
            vertex[size].index = i;
        }
        if (k) {
            vertex[size].prior = -1;
            vertex[size].distance = INFINITY;
            vertex[size].type = SINK;
        }
    }

    /* Relax distances */
    for (k = 0; k < size; k++) {
        for (i = 0; i < size; i++) {
            vertex_t *v = &vertex[i];
            int next;
            double dist;
            if (v->type == POLICE) {
                if (police[v->index].bank == -1) {
                    next = size;
                    dist = v->distance;
                }
                else {
                    next = police[v->index].bank;
                    dist = v->distance - bank[next].distance[v->index];
                }
                if (dist < vertex[next].distance) {
                    vertex[next].distance = dist;
                    vertex[next].prior = i;
                }
            }
            else {
                for (j = 0; j < m; j++) {
                    if (bank[i].police != j) {
                        dist = vertex[i].distance + bank[i].distance[j];
                        next = n + j;
                        if (dist < vertex[next].distance) {
                            vertex[next].distance = dist;
                            vertex[next].prior = i;
                        }
                    }
                }
            }
        }
    }
    
    /* Assign new relations */
    current = vertex[size].prior;
    while (current != -1) {
        int p = vertex[current].index, b = vertex[current].prior;
        bank[b].police = p;
        police[p].bank = b;
        current = vertex[b].prior;
    }
}

/* Find minimum cost assignment */
double find_minimum_cost() {
    double average;
    int i;
    for (i = 0; i < n; i++)
        bank[i].police = -1;
    for (i = 0; i < m; i++)
        police[i].bank = -1;
    for (i = 0; i < n; i++)
        augment_shortest_path_bellman_ford();
    for (i = 0, average = 0; i < n; i++)
        average += bank[i].distance[bank[i].police];
    return average / n;
}

/* Main function */
int main() {
    while (scanf("%d %d", &n, &m) != EOF && n > 0) {
        int i, j;
        for (i = 0; i < n; i++) 
            for (j = 0; j < m; j++)
                assert(scanf("%lf", &bank[i].distance[j]) != EOF);
        printf("%.2f\n", find_minimum_cost() + EPSILON);
    }
    return EXIT_SUCCESS;
}
