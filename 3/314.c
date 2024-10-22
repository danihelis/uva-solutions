/* 314
 * Robot
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     50
#define NUM_DIRS    4
#define MAX_MAZE    (MAX_DIM * MAX_DIM * NUM_DIRS)
#define INFINITY    (1 << 30)

typedef enum {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} direction_t;

typedef struct {
    int row, column;
} point_t;

typedef struct {
    point_t pos;
    direction_t dir;
    int visited, distance, queued, blocked;
} cell_t;

int block[MAX_DIM][MAX_DIM];
int rows, columns;
point_t start, end;
direction_t init_dir;

/* Shortest path */
int find_shortest_path() {
    cell_t maze[MAX_DIM][MAX_DIM][NUM_DIRS], *queue[MAX_MAZE];
    int front, rear, minimum;
    int i, j, k, br, bc;

    /* Initialize maze */
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            for (k = 0; k < NUM_DIRS; k++) {
                cell_t *c = &maze[i][j][k];
                c->pos.row = i, c->pos.column = j, c->dir = k;
                c->visited = 0, c->queued = 0, c->blocked = 0; 
                c->distance = INFINITY;
            }

    /* Define blocked cells */
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            if (block[i][j])
                for (br = -1; br <= 0; br++)
                    for (bc = -1; bc <= 0; bc++)
                        if (i + br >= 0 && j + bc >= 0)
                            for (k = 0; k < NUM_DIRS; k++)
                                maze[i + br][j + bc][k].blocked = 1;

    /* BFS */
    queue[0] = &maze[start.row][start.column][init_dir];
    queue[0]->distance = 0, queue[0]->queued = 1;
    front = 0, rear = 1;
    while (front < rear) {

        cell_t *cur = queue[front++];
        point_t *p = &cur->pos;
        cur->visited = 1;

        /* Solution found */
        if (p->row == end.row && p->column == end.column) {
            return cur->distance;
        }

        /* Change direction */
        for (k = 0; k < NUM_DIRS; k++)
            if (k + cur->dir) {
                int dist = cur->distance + (k % 2 == cur->dir % 2 ? 2 : 1);
                cell_t *n = &maze[p->row][p->column][k];
                if (!n->visited && n->distance > dist) {
                    n->distance = dist;
                    if (!n->queued) {
                        queue[rear++] = n;
                        n->queued = 1;
                    }
                }
            }

        /* Visit next K+1 cells */
        for (k = 1; k <= 3; k++) {
            br = p->row + k * (cur->dir == NORTH ? -1 : 
                    cur->dir == SOUTH ? 1 : 0);
            bc = p->column + k * (cur->dir == EAST ? 1 : 
                    cur->dir == WEST ? -1 : 0);
            if (br >= 0 && br < rows - 1 && bc >= 0 && bc < columns - 1 &&
                    !maze[br][bc][cur->dir].blocked) {
                cell_t *n = &maze[br][bc][cur->dir];
                if (!n->visited && n->distance > cur->distance + 1) {
                    n->distance = cur->distance + 1;
                    if (!n->queued) {
                        queue[rear++] = n;
                        n->queued = 1;
                    }
                }
            }
            else 
                break;
        }

        /* Choose nearest as next element */
        for (i = front + 1, minimum = front; i < rear; i++)
            if (queue[i]->distance < queue[minimum]->distance)
                minimum = i;
        if (minimum != front) {
            cell_t *swap = queue[minimum];
            queue[minimum] = queue[front];
            queue[front] = swap;
        }
    }
    return -1;
}

/* Main function */
int main() {
    while (scanf("%d %d", &rows, &columns) != EOF && rows > 0) {
        int i, j;
        char dir;
        for (i = 0; i < rows; i++)
            for (j = 0; j < columns; j++) 
                assert(scanf("%d", &block[i][j]) != EOF);
        for (i = 0; i < 2; i++) {
            point_t *p = (i == 0 ? &start : &end);
            assert(scanf("%d %d", &p->row, &p->column) != EOF);
            p->row--, p->column--;
        }
        assert(scanf(" %c%*[^\n]", &dir) != EOF);
        init_dir = dir == 'n' ? NORTH : dir == 's' ? SOUTH :
                dir == 'w' ? WEST : EAST;
        printf("%d\n", find_shortest_path());
    }
    return EXIT_SUCCESS;
}
