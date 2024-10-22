/* 11167
 * Monkeys in the Emei Mountain
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES       100
#define MAX_INTERVALS   (2 * MAX_NODES)
#define MAX_WINDOWS     (2 * MAX_INTERVALS)
#define MAX_VERTICES    (MAX_NODES + MAX_INTERVALS + 2)

#define INFINITY        1000000
#define SOURCE          0
#define SINK            1
#define NODE(n)         (2 + n)
#define V2INTER(v)      (v - 2 - num_nodes)
#define INTERVAL(i)     (2 + num_nodes + i)

#define MIN(x,y)        ((x) < (y) ? (x) : (y))
#define MAX(x,y)        ((x) > (y) ? (x) : (y))

typedef struct {
    int start, end, diff, offset;
} interval_t;

typedef struct {
    int start, end;
} window_t;

typedef struct {
    int start, end, volume;
    window_t window[MAX_WINDOWS];
    int num_windows;
} node_t;

typedef struct vertex_s {
    int edge[MAX_VERTICES], num_edges;
} vertex_t;

interval_t interval[MAX_INTERVALS];
node_t node[MAX_NODES];
int num_nodes, num_intervals, multi, total_volume;

vertex_t vertex[MAX_VERTICES];
int capacity[MAX_VERTICES][MAX_VERTICES], flow[MAX_VERTICES][MAX_VERTICES];
int num_vertices;

/* Compare numbers */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Create intervals */
void create_intervals() {
    int i, points[MAX_INTERVALS];
    for (i = 0; i < num_nodes; i++) {
        points[i * 2] = node[i].start;
        points[i * 2 + 1] = node[i].end;
    }
    qsort(points, num_nodes * 2, sizeof (int), compare);
    for (i = 1, num_intervals = 0; i < 2 * num_nodes; i++)
        if (points[i] != points[i - 1]) {
            interval_t *inter = &interval[num_intervals++];
            inter->start = points[i - 1];
            inter->end = points[i];
            inter->diff = inter->end - inter->start;
        }
}

/* Create graph */
#define ADD_EDGE(i0, i1, cap)   do { \
        vertex[i0].edge[vertex[i0].num_edges++] = i1; \
        vertex[i1].edge[vertex[i1].num_edges++] = i0; \
        capacity[i0][i1] = cap, capacity[i1][i0] = 0; \
        flow[i0][i1] = 0, flow[i1][i0] = 0; \
    } while (0)

void create_graph() {
    int i, k;
    num_vertices = num_nodes + num_intervals + 2;
    for (i = 0; i < num_vertices; i++)
        vertex[i].num_edges = 0;
    for (i = 0; i < num_nodes; i++) {
        ADD_EDGE(SOURCE, NODE(i), node[i].volume);
        for (k = 0; k < num_intervals && 
                node[i].end > interval[k].start; k++)
            if (node[i].start <= interval[k].start)
                ADD_EDGE(NODE(i), INTERVAL(k), interval[k].diff);
    }
    for (k = 0; k < num_intervals; k++)
        ADD_EDGE(INTERVAL(k), SINK, interval[k].diff * multi);
}

/* Find maximum flow */
int find_maximum_flow() {
    int total_flow = 0;
    do {
        int prior[MAX_VERTICES], local_flow[MAX_VERTICES], 
            queue[MAX_VERTICES];
        int i, front, rear, found_sink, allowed_flow;
        
        /* Find shortest path from source to sink */
        memset(prior, -1, num_vertices * sizeof (int));
        queue[0] = SOURCE, front = 0, rear = 1;
        found_sink = 0;
        while (front < rear && !found_sink) {
            int v = queue[front++];
            for (i = 0; !found_sink && i < vertex[v].num_edges; i++) {
                int n = vertex[v].edge[i];
                if (n != SOURCE && prior[n] == -1 && 
                        capacity[v][n] > flow[v][n]) {
                    queue[rear++] = n;
                    prior[n] = v;
                    local_flow[n] = capacity[v][n] - flow[v][n];
                    found_sink = (n == SINK);
                }
            }
        }
        if (!found_sink)
            break;

        /* Update flow along the path */
        allowed_flow = INFINITY;
        for (i = 1; prior[i] != -1; i = prior[i])
            allowed_flow = MIN(allowed_flow, local_flow[i]);
        for (i = 1; prior[i] != -1; i = prior[i]) {
            flow[prior[i]][i] += allowed_flow;
            flow[i][prior[i]] -= allowed_flow;
        }
        total_flow += allowed_flow;
    } while (total_flow < total_volume);

    return total_flow == total_volume;
}

/* Add a window to a node */
void add_window(node_t *n, window_t *win) {
    if (n->num_windows == 0 || 
            n->window[n->num_windows - 1].end < win->start)
        n->window[n->num_windows++] = *win;
    else
        n->window[n->num_windows - 1].end = win->end;
}

/* Distribute windows of time from intervals for each node */
void distribute_windows() {
    window_t window;
    int i, k;
    for (k = 0; k < num_intervals; k++)
        interval[k].offset = 0;
    for (i = 0; i < num_nodes; i++) {
        node_t *n = &node[i];
        n->num_windows = 0;
        for (k = 1; k < vertex[NODE(i)].num_edges; k++) {
            int e = vertex[NODE(i)].edge[k];
            interval_t *inter = &interval[V2INTER(e)];
            int amount = flow[NODE(i)][e];
            if (amount > 0) {
                window.start = inter->start + inter->offset;
                window.end = MIN(inter->start + inter->offset + amount, 
                        inter->end);
                inter->offset = (inter->offset + amount) % inter->diff;
                if (amount == window.end - window.start) 
                    add_window(n, &window);
                else {
                    window_t remain;
                    remain.start = inter->start;
                    remain.end = inter->start + inter->offset;
                    add_window(n, &remain);
                    add_window(n, &window);
                }
            }
        }
    }
}

/* Print windows */
void print_windows() {
    int i, k;
    for (i = 0; i < num_nodes; i++) {
        node_t *n = &node[i];
        printf("%d", n->num_windows);
        for (k = 0; k < n->num_windows; k++)
            printf(" (%d,%d)", n->window[k].start, n->window[k].end);
        printf("\n");
    }
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d %d", &num_nodes, &multi) != EOF && num_nodes > 0) {
        int i, able;
        for (i = 0, total_volume = 0; i < num_nodes; i++) {
            node_t *n = &node[i];
            assert(scanf("%d %d %d", &n->volume, &n->start, &n->end) != EOF);
            total_volume += n->volume;
        }
        create_intervals();
        create_graph();
        able = find_maximum_flow();

        printf("Case %d: %s\n", ++test, able ? "Yes" : "No");
        if (able) {
            distribute_windows();
            print_windows();
        }
    }
    return EXIT_SUCCESS;
}
