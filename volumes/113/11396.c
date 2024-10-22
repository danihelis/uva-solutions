/* 11396
 * Claw Decomposition
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    300
#define NUM_EDGES       3

typedef enum {
    WHITE = 0,
    BLACK = 1,
    NONE
} color_t;

typedef struct vertex_s {
    struct vertex_s *edge[NUM_EDGES];
    color_t color;
    int degree;
} vertex_t;

vertex_t vertex[MAX_VERTICES];
int num_vertices;

/* Color the graph using two colors */ 
int bicolor() {
    vertex_t *queue[MAX_VERTICES];
    int i, j, front, rear; 
    for (i = 0; i < num_vertices; i++)
        vertex[i].color = NONE;
    for (i = 0; i < num_vertices; i++) {
        vertex_t *v = &vertex[i];
        if (v->color == NONE) {
            v->color = WHITE;
            queue[0] = v, front = 0, rear = 1;
            while (front < rear) {
                v = queue[front++];
                for (j = 0; j < NUM_EDGES; j++)
                    if (v->edge[j]->color == NONE) {
                        v->edge[j]->color = 1 - v->color;
                        queue[rear++] = v->edge[j];
                    }
                    else if (v->edge[j]->color == v->color)
                        return 0;
            }
        }
    }
    return 1;
}

/* Main function */
int main() {
    while (scanf("%d", &num_vertices) != EOF && num_vertices > 0) {
        int i, j;
        for (i = 0; i < num_vertices; i++)
            vertex[i].degree = 0;
        while (scanf("%d %d", &i, &j) != EOF && i > 0) {
            vertex_t *a = &vertex[--i], *b = &vertex[--j];
            a->edge[a->degree++] = b;
            b->edge[b->degree++] = a;
        }
        printf("%s\n", bicolor() ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
