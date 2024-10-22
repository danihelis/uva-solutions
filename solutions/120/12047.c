/* 12047
 * Highest Paid Toll
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_V       10000
#define MAX_E       100000
#define MAX(x, y)   ((x) > (y) ? (x) : (y))
#define MIN(x, y)   ((x) < (y) ? (x) : (y))

#define PARENT(x)       (((x) - 1) / 2)
#define CHILD(x)        (2 * (x) + 1)
#define SMALLER(x, y)   (heap[x].dist < heap[y].dist)
#define SWAP(x, y)      do { \
        choice_t _swap = heap[x]; heap[x] = heap[y]; heap[y] = _swap; \
    } while (0)

typedef struct {
    int source, destiny, cost;
} edge_t; 

typedef struct {
    int visited, num_edges;
    edge_t *edges, *coming;
    int distance, costest;
} vertex_t;

typedef struct {
    edge_t *edge;
    int dist;
} choice_t;

vertex_t vertex[MAX_V];
edge_t edge[MAX_E];
choice_t heap[MAX_E];
int num_vertices, num_edges, heap_size;

/* Insert into heap */
void insert_heap(choice_t choice) {
    int parent, index = heap_size++;
    heap[index] = choice;
    while (index > 0) {
        parent = PARENT(index);
        if (SMALLER(index, parent))
            SWAP(parent, index);
        else 
            break;
        index = parent;
    }
}

/* Remove minimum from heap */
choice_t remove_heap() {
    int child, index = 0;
    choice_t minimum = heap[0];
    heap[index] = heap[--heap_size];
    while ((child = CHILD(index)) < heap_size) {
        if (child + 1 < heap_size && SMALLER(child + 1, child))
            child++;
        if (SMALLER(child, index))
            SWAP(child, index);
        else 
            break;
        index = child;
    }
    return minimum;
}

/* Compare edges for sorting */
int compare_edge(const void *a, const void *b) {
    return ((edge_t *) a)->source - ((edge_t *) b)->source;
}

/* Reconstruct a path from origin to a vertice */
void reconstruct(choice_t choice) {
    vertex_t *v;
    edge_t *e = choice.edge;
    int dist = vertex[e->destiny].distance, 
        costest = vertex[e->destiny].costest;
    while (e != NULL) {
        dist += e->cost;
        costest = MAX(e->cost, costest);
        v = &vertex[e->source];
        v->distance = MIN(dist, v->distance);
        v->costest = MAX(costest, v->costest);
        e = v->coming;
    }
}

/* Find shortest edge to destiny whose path is lower than cost */
int costest_edge(int source, int destiny, int max_cost) {
    int i, j, num_circles;
    choice_t choice, enqueue, circle[MAX_E];
    vertex_t *v, *d;
    edge_t *e;

    qsort(edge, num_edges, sizeof (edge_t), compare_edge);
    for (i = 0, e = &edge[0]; i < num_vertices; i++) {
        v = &vertex[i];
        v->visited = 0, v->distance = 1 << 30, v->costest = -1;
        v->edges = e->source == i ? e : NULL;
        v->coming = NULL;
        e += v->num_edges;
    }
    heap_size = num_circles = 0;
    choice.edge = NULL, choice.dist = 0;
    insert_heap(choice);
    d = &vertex[destiny];
    d->distance = 0, d->costest = 0;

    while (heap_size > 0) {
        choice = remove_heap();
        v = &vertex[choice.edge == NULL ? source : choice.edge->destiny];
        if (v == d)
            reconstruct(choice);
        if (v->visited) {
            if (v != d)
                circle[num_circles++] = choice;
            continue;
        }
        v->visited = 1;
        v->coming = choice.edge;
        for (e = v->edges, i = 0; i < v->num_edges; i++, e++) {
            int dist = choice.dist + e->cost;
            if (dist <= max_cost) {
                enqueue.edge = e, enqueue.dist = dist;
                insert_heap(enqueue);
            }
        }
    }

    while (num_circles > 0) {
        for (i = 1, j = 0; i < num_circles; i++)
            if (vertex[circle[i].edge->destiny].distance < 
                    vertex[circle[j].edge->destiny].distance)
                j = i;
        choice = circle[j];
        circle[j] = circle[--num_circles];
        if (choice.dist + vertex[choice.edge->destiny].distance <= max_cost)
            reconstruct(choice);
    }
    return vertex[source].costest;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, source, destiny, max_cost;
        assert(scanf("%d %d %d %d %d", &num_vertices, &num_edges, 
                    &source, &destiny, &max_cost) == 5);
        for (i = 0; i < num_vertices; i++)
            vertex[i].num_edges = 0;
        for (i = 0; i < num_edges; i++) {
            edge_t *e = &edge[i];
            assert(scanf("%d %d %d", &e->source, &e->destiny, 
                        &e->cost) == 3);
            e->source--, e->destiny--;
            vertex[e->source].num_edges++;
        }
        printf("%d\n", costest_edge(--source, --destiny, max_cost));
    }
    return EXIT_SUCCESS;
}
