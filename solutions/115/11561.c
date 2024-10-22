/* 11561
 * Getting Gold
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50
#define MAX_STR     (MAX_N + 2)
#define MAX_DIM     (MAX_N * MAX_N)

#define MAX_MOVES   4
#define IN(x,max)   (x >= 0 && x < max)

#define WALL        '#'
#define TRAP        'T'
#define GOLD        'G'
#define FLOOR       '.'
#define START       'P'

typedef struct {
    int row, col;
} coord_t;

char map[MAX_N][MAX_STR];
char visited[MAX_N][MAX_N], safe[MAX_N][MAX_N];
int num_rows, num_cols;

/* Return number of gold pieces that can be retrieved */
int get_gold() {
    coord_t queue[MAX_DIM], start;
    int dr[MAX_MOVES] = {1, 0, -1, 0}, dc[MAX_MOVES] = {0, 1, 0, -1};
    int r, c, d, front, rear, gold;
    for (r = 0; r < num_rows; r++) {
        for (c = 0; c < num_cols; c++) {
            visited[r][c] = 0, safe[r][c] = 1;
            if (map[r][c] == START) start.row = r, start.col = c;
        }
    }
    for (r = 0; r < num_rows; r++) {
        for (c = 0; c < num_cols; c++) {
            if (map[r][c] == TRAP) {
                for (d = 0; d < MAX_MOVES; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (IN(nr, num_rows) && IN(nc, num_cols)) safe[nr][nc] = 0;
                }
            }
        }
    }
    queue[0] = start, front = 0, rear = 1;
    visited[start.row][start.col] = 1;
    gold = 0;
    while (front < rear) {
        coord_t c = queue[front++];
        if (map[c.row][c.col] == GOLD) gold++;
        if (!safe[c.row][c.col]) continue;
        for (d = 0; d < MAX_MOVES; d++) {
            int nr = c.row + dr[d], nc = c.col + dc[d];
            if (IN(nr, num_rows) && IN(nc, num_cols)) {
                if (visited[nr][nc] || map[nr][nc] == WALL) continue;
                queue[rear].row = nr, queue[rear].col = nc;
                rear++;
                visited[nr][nc] = 1;
            }
        }
    }
    return gold;
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_cols, &num_rows) == 2) {
        int i;
        for (i = 0; i < num_rows; i++) {
            assert(scanf(" %s", map[i]) == 1);
        }
        printf("%d\n", get_gold());
    }
    return EXIT_SUCCESS;
}
