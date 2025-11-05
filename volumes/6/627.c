/* 627
 * The Net
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES    300
#define MAX_EDGES       50
#define MAX_STRING      300

typedef struct vertex_s {
    int id;
    struct vertex_s *edges[MAX_EDGES];
    int num_edges;
    int distance;
    char enqueued;
    struct vertex_s *parent;
} vertex_t;

vertex_t vertices[MAX_VERTICES];
vertex_t *dict[MAX_VERTICES];
int num_vertices;


/* Get or insert vertex */
vertex_t *get_or_insert(int id, char may_insert) {
    int start = 0, end = num_vertices;
    while (start < end) {
        int middle = (start + end) / 2;
        vertex_t *v = dict[middle];
        if (v->id == id) return v;
        else if (v->id < id) start = middle + 1;
        else end = middle;
    }
    if (!may_insert) return NULL;
    for (end = num_vertices; end > start; end--) {
        dict[end] = dict[end - 1];
    }
    dict[start] = &vertices[num_vertices++];
    dict[start]->id = id;
    dict[start]->num_edges = 0;
    return dict[start];
}


/* Read vertex edges */
void read_vertex_entry() {
    char string[MAX_STRING], *token;
    int id;
    vertex_t *vertex;

    string[0] = 0;
    assert(scanf("%d-%[^\n] ", &id, string) >= 1);
    vertex = get_or_insert(id, 1);

    for (token = strtok(string, ","); token; token = strtok(NULL, ",")) {
        vertex_t *v = get_or_insert(atoi(token), 1);
        vertex->edges[vertex->num_edges++] = v;
    }
}


/* Find and print shortest path between two vertices */
void print_shortest_path(vertex_t *start, vertex_t *end) {
    vertex_t *queue[MAX_VERTICES];
    int i, rear, front;

    for (i = 0; i < num_vertices; i++) {
        vertex_t *v = dict[i];
        v->enqueued = 0;
        v->parent = NULL;
    }
    queue[0] = start, front = 0, rear = 1;
    start->enqueued = 1, start->distance = 0;

    while (front < rear) {
        vertex_t *v = queue[front++];
        if (v == end) break;
        for (i = 0; i < v->num_edges; i++) {
            vertex_t *n = v->edges[i];
            if (!n->enqueued) {
                queue[rear++] = n, n->enqueued = 1;
                 n->parent = v, n->distance = v->distance + 1;
            }
        }
    }

    if (!end->enqueued) printf("connection impossible\n");
    else {
        vertex_t *v = end;
        rear = 0;
        while (v) {
            queue[rear++] = v;
            v = v->parent;
        }
        for (i = rear - 1; i >= 0; i--) {
            printf("%d%c", queue[i]->id, i == 0 ? '\n' : ' ');
        }
    }
}


/* Main function */
int main() {
    int num_entries;
    while (scanf("%d", &num_entries) == 1) {
        num_vertices = 0;
        while (num_entries-- > 0) {
            read_vertex_entry();
        }

        assert(scanf("%d", &num_entries) == 1);
        printf("-----\n");
        while (num_entries-- > 0) {
            int a, b;
            vertex_t *start, *end;
            assert(scanf("%d %d", &a, &b) == 2);
            start = get_or_insert(a, 0);
            end = get_or_insert(b, 0);
            if (!start || !end) printf("connection impossible\n");
            else print_shortest_path(start, end);
        }
    }
    return EXIT_SUCCESS;
}
