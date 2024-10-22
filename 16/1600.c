/* 1600
 * Patrol Robot
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     20
#define MAX_POWER   20
#define MAX_HEAP    (MAX_DIM * MAX_DIM * MAX_POWER * MAX_POWER)
#define INFINITY    100000

#define IN(x, max)  ((x) >= 0 && (x) < (max))

#define PARENT(i)   (((i) - 1) / 2)
#define CHILD(i)    (2 * (i) + 1)
#define SWAP(a, b)  do { \
    point_t swap = heap[a]; \
    heap[a] = heap[b]; \
    heap[b] = swap; \
    a = b; \
} while (0)


typedef struct {
    int row, col, power, distance;
} point_t;

typedef struct {
    int blocked;
    int best_distance[MAX_POWER + 1];
} cell_t;

cell_t maze[MAX_DIM][MAX_DIM];
int rows, columns, max_power;

point_t heap[MAX_HEAP];
int heap_size;


/* Check which element of the heap is better between two indices */
int is_better(int a, int b) {
    point_t *pa = &heap[a], *pb = &heap[b];
    if (pa->distance == pb->distance) return pa->power > pb->power;
    return pa->distance < pb->distance;
}

/* Insert into heap */
void insert_heap(point_t value) {
    int index = heap_size++;
    assert(heap_size <= MAX_HEAP);
    heap[index] = value;
    while (index > 0 && is_better(index, PARENT(index))) {
        SWAP(index, PARENT(index));
    }
}

/* Remove from heap */
point_t remove_heap() {
    point_t value = heap[0];
    int index = 0, child;
    heap[index] = heap[--heap_size];
    while ((child = CHILD(index)) < heap_size) {
        if (child + 1 < heap_size && is_better(child + 1, child)) child++;
        if (is_better(index, child)) break;
        SWAP(index, child);
    }
    return value;
}

/* Find exit from maze */
int find_exit() {
    int dr[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0};
    point_t start, point, next;
    cell_t *cell, *next_cell;
    int r, c, d, k, skip;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < columns; c++) {
            for (k = 0; k <= max_power; k++) {
                maze[r][c].best_distance[k] = INFINITY;
            }
        }
    }
    start.row = 0, start.col = 0, start.power = max_power, start.distance = 0;
    heap_size = 0;
    insert_heap(start);
    while (heap_size > 0) {
        point = remove_heap();
        cell = &maze[point.row][point.col];
        for (d = 0; d < 4; d++) {
            next.row = point.row + dr[d], next.col = point.col + dc[d];
            if (!IN(next.row, rows) || !IN(next.col, columns)) continue;
            next_cell = &maze[next.row][next.col];
            next.power = next_cell->blocked ? point.power - 1 : max_power;
            next.distance = point.distance + 1;
            if (next.power < 0) continue;
            for (k = next.power, skip = 0; !skip && k <= max_power; k++) {
                skip = next.distance >= next_cell->best_distance[k];
            }
            if (skip) continue;
            if (next.row == rows - 1 && next.col == columns - 1) {
                return next.distance;
            }
            next_cell->best_distance[next.power] = next.distance;
            insert_heap(next);
        }
    }
    return -1;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int r, c;
        assert(scanf("%d %d %d", &rows, &columns, &max_power) != EOF);
        for (r = 0; r < rows; r++) {
            for (c = 0; c < columns; c++) {
                assert(scanf("%d", &maze[r][c].blocked) != EOF);
            }
        }
        printf("%d\n", rows > 1 || columns > 1 ? find_exit() : 0);
    }
    return EXIT_SUCCESS;
}
