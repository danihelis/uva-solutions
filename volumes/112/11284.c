/* 11284
 * Shopping Trip
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    51
#define MAX_EDGES       (MAX_VERTICES * MAX_VERTICES)
#define MAX_HEAP_SIZE   (2 * MAX_EDGES)
#define INFINITY        100000000

#define MAX_NODES       12
#define DP_SOURCE       4
#define DP_BITS         (DP_SOURCE + MAX_NODES)
#define DP_LENGTH       (1 << DP_BITS)

/* Heap ---------------------------------------------------------------- */

typedef struct {
    int vertex, cost;
} info_t;

info_t heap[MAX_HEAP_SIZE];
int heap_size;

#define PARENT(i)       ((i - 1) / 2)
#define CHILD(i)        (2 * (i) + 1)

#define HEAP_SWAP(i,j) do { \
        info_t swap = heap[i]; \
        heap[i] = heap[j]; \
        heap[j] = swap; \
        i = j; \
    } while (0)

/* Add a new element into the heap */
void add_heap(int vertex, int cost) {
    int index = heap_size++;
    assert(heap_size < MAX_HEAP_SIZE);
    heap[index].vertex = vertex, heap[index].cost = cost;
    while (index > 0 && heap[index].cost < heap[PARENT(index)].cost)
        HEAP_SWAP(index, PARENT(index));
}

/* Remove top element from heap (with lowest cost) */
info_t remove_heap() {
    int index = 0, child;
    info_t minimum = heap[0];
    heap[0] = heap[--heap_size];
    while ((child = CHILD(index)) < heap_size) {
        if (child + 1 < heap_size && heap[child + 1].cost < heap[child].cost)
            child++;
        if (heap[child].cost < heap[index].cost)
            HEAP_SWAP(index, child);
        else
            break;
    }
    return minimum;
}

/* Graph ---------------------------------------------------------------- */

typedef struct {
    int cost[MAX_VERTICES];
} vertex_t;

vertex_t vertex[MAX_VERTICES];
int num_vertices;

/* Compute minimum distance between two vertices */
int get_minimum_distance(int start, int end) {
    char visited[MAX_VERTICES];
    int i;
    memset(visited, 0, num_vertices);
    heap[0].vertex = start, heap[0].cost = 0, heap_size = 1;
       
    while (heap_size > 0) {
        info_t cur = remove_heap();
        if (cur.vertex == end)
            return cur.cost;
        visited[cur.vertex] = 1;
        for (i = 0; i < num_vertices; i++) {
            int cost = vertex[cur.vertex].cost[i];
            if (!visited[i] && cost < INFINITY)
                add_heap(i, cur.cost + cost);
        }
    }
    assert(NULL);
    return INFINITY;
}

/* Dynamic Programming -------------------------------------------------- */

int node[MAX_NODES + 1], saving[MAX_NODES + 1];
int num_nodes;
int distance[MAX_NODES + 1][MAX_NODES + 1];
int dp_table[DP_LENGTH];
char dp_defined[DP_LENGTH];

/* Compute minimum cost to visit a set of nodes (DP) */
int compute_best_save(int source, int set) {
    int code = source | (set << DP_SOURCE);
    int i, value;
    if (dp_defined[code])
        return dp_table[code];
    else if (set == 0)
        value = saving[source] - distance[source][num_nodes];
    else {
        value = -INFINITY;
        for (i = 0; i < num_nodes; i++)
            if (set & (1 << i)) {
                int new_value = saving[source] - distance[source][i] + 
                        compute_best_save(i, set ^ (1 << i));
                if (new_value > value)
                    value = new_value;
                new_value = compute_best_save(source, set ^ (1 << i));
                if (new_value > value)
                    value = new_value;
            }
    }

    dp_defined[code] = 1;
    dp_table[code] = value;
    return value;
}

/* Main ------------------------------------------------------------------ */

#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Define nodes and compute distances and costs */
int read_define_and_compute() {
    int vertex2node[MAX_VERTICES];
    int i, j, n, best;

    /* Read graph */
    assert(scanf("%d %d", &num_vertices, &n) != EOF);
    for (i = 0, num_vertices++; i < num_vertices; i++)
        for (j = 0; j < num_vertices; j++)
            vertex[i].cost[j] = INFINITY;
    for (; n > 0; n--) {
        int v1, v2, c1, c2, c;
        assert(scanf("%d %d %d.%d", &v1, &v2, &c1, &c2) != EOF);
        c = c1 * 100 + c2;
        vertex[v1].cost[v2] = MIN(vertex[v1].cost[v2], c);
        vertex[v2].cost[v1] = MIN(vertex[v2].cost[v1], c);
    }

    /* Define nodes */
    assert(scanf("%d", &n) != EOF);
    memset(vertex2node, -1, num_vertices * sizeof (int));
    memset(saving, 0, (n + 1) * sizeof (int));
    for (num_nodes = 0; n > 0; n--) {
        int v, c1, c2;
        assert(scanf("%d %d.%d", &v, &c1, &c2) != EOF);
        if (vertex2node[v] == -1) {
            vertex2node[v] = num_nodes;
            node[num_nodes++] = v;
        }
        saving[vertex2node[v]] += c1 * 100 + c2;
    }
    node[num_nodes] = 0;

    /* Define minimum distances */
    for (i = 0; i <= num_nodes; i++) {
        distance[i][i] = 0;
        for (j = i + 1; j <= num_nodes; j++)
            distance[i][j] = distance[j][i] = 
                    get_minimum_distance(node[i], node[j]);
    }

    /* Compute minimum cost */
    memset(dp_defined, 0, DP_LENGTH);
    best = compute_best_save(num_nodes, (1 << num_nodes) - 1);

    return best;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int value = read_define_and_compute();
        if (value <= 0)
            printf("Don't leave the house\n");
        else 
            printf("Daniel can save $%d.%02d\n", value / 100, value % 100);
    }
    return EXIT_SUCCESS;
}
