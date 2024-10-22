/* 10653
 * Bombs! NO they are Mines!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIR     4
#define MAX_DIM     1000
#define MAX_STACK   (MAX_DIM * MAX_DIM)
#define INFINITY    (1 << 30)
#define IN(x, v)    ((x) >= 0 && (x) < (v))
#define MAX_STRING  (MAX_DIM * 10)

typedef struct {
    int row, col, blocked, dist, visited, queued;
} point_t;

point_t map[MAX_DIM][MAX_DIM];
int rows, columns;
point_t *source, *destiny;

/* Shortest distance */
int shortest_distance() {
    point_t *queue[MAX_STACK];
    int i, j, k, front, rear;
    int drow[MAX_DIR] = {0, 1, 0, -1}, dcol[MAX_DIR] = {1, 0, -1, 0};

    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++) {
            point_t *p = &map[i][j];
            p->dist = INFINITY;
            p->visited = p->queued = 0;
        }

    queue[0] = source, front = 0, rear = 1;
    source->dist = 0;
    while (front < rear) {
        point_t *p = queue[front++];
        if (p == destiny)
            return p->dist;
        p->visited = 1;
        for (k = 0; k < MAX_DIR; k++) {
            i = p->row + drow[k], j = p->col + dcol[k];
            if (IN(i, rows) && IN(j, columns)) {
                point_t *n = &map[i][j];
                int new_dist = p->dist + 1;
                if (!n->blocked && !n->visited && new_dist < n->dist) {
                    n->dist = new_dist;
                    if (!n->queued)
                        queue[rear++] = n, n->queued = 1;
                }
            }
        }
    }
    return INFINITY;
}

/* Main function */
int main() {
    while (scanf("%d %d", &rows, &columns) != EOF && rows > 0) {
        int i, j, k, num_blocked_rows;
        for (i = 0; i < rows; i++)
            for (j = 0; j < columns; j++) {
                point_t *p = &map[i][j];
                p->row = i, p->col = j, p->blocked = 0;
            }
        assert(scanf("%d", &num_blocked_rows) != EOF);
        for (; num_blocked_rows > 0; num_blocked_rows--) {
            assert(scanf("%d %d", &i, &k) != EOF);
            for (; k > 0; k--) {
                assert(scanf("%d", &j) != EOF);
                map[i][j].blocked = 1;
            }
        }
        for (k = 0; k < 2; k++) {
            assert(scanf("%d %d", &i, &j) != EOF);
            (k ? (destiny = &map[i][j]) : (source = &map[i][j]));
        }
        printf("%d\n", shortest_distance());
    }
    return EXIT_SUCCESS;
}
