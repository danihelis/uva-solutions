/* 929
 * Number Maze
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     1000
#define MAX_HEAP    (4 * MAX_DIM * MAX_DIM)

typedef struct {
    int row, col, distance;
} pair_t;

typedef struct {
    int cost, distance;
    char visited;
} cell_t;

cell_t matrix[MAX_DIM][MAX_DIM];
pair_t heap[MAX_HEAP];
int rows, columns, size;

#define IN(val, max)    ((val) >= 0 && (val) < (max))
#define PARENT(x)       (((x) - 1) / 2)
#define CHILD(x)        (2 * (x) + 1)
#define SWAP(x, y)      do { \
        pair_t swap = heap[x]; \
        heap[x] = heap[y]; \
        heap[y] = swap; \
    } while (0)

/* Insert into heap */
void insert(pair_t pair) {
    int index = size++;
    heap[index] = pair;
    while (index > 0 && 
            heap[PARENT(index)].distance > heap[index].distance) {
        SWAP(index, PARENT(index));
        index = PARENT(index);
    }
}

/* Remove minimum from heap */
pair_t remove_minimum() {
    pair_t removed = heap[0];
    int index = 0;
    heap[0] = heap[--size];
    while (CHILD(index) < size) {
        int child = CHILD(index);
        if (child + 1 < size && 
                heap[child + 1].distance < heap[child].distance)
            child++;
        if (heap[child].distance < heap[index].distance) {
            SWAP(index, child);
            index = child;
        } else
            break;
    }
    return removed;
}

/* Find shortest route */
int find_shortest_route() {
    int drow[4] = {-1, 0, 1, 0}, dcol[4] = {0, 1, 0, -1};
    pair_t pos, new_pos;
    cell_t *v;
    int i;

    matrix[0][0].distance = matrix[0][0].cost;
    pos.row = 0, pos.col = 0, pos.distance = matrix[0][0].distance;
    size = 0;
    insert(pos);

    while (size > 0) {
        pos = remove_minimum();
        v = &matrix[pos.row][pos.col];
        if (pos.row == rows - 1 && pos.col == columns - 1)
            return v->distance;
        if (v->visited)
            continue;
        v->visited = 1;
        for (i = 0; i < 4; i++) {
            new_pos.row = pos.row + drow[i];
            new_pos.col = pos.col + dcol[i];
            if (IN(new_pos.row, rows) && IN(new_pos.col, columns)) {
                cell_t *n = &matrix[new_pos.row][new_pos.col];
                if (!n->visited && (n->distance < 0 || 
                            n->distance > v->distance + n->cost)) {
                    n->distance = v->distance + n->cost;
                    new_pos.distance = n->distance;
                    insert(new_pos);
                }
            }
        }
    }
    assert(NULL); /* no path found */
    return 0;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j;
        assert(scanf("%d %d", &rows, &columns) != EOF);
        for (i = 0; i < rows; i++)
            for (j = 0; j < columns; j++) {
                cell_t *c = &matrix[i][j];
                assert(scanf("%d", &c->cost) != EOF);
                c->distance = -1;
                c->visited = 0;
            }
        printf("%d\n", find_shortest_route());
    }
    return EXIT_SUCCESS;
}
