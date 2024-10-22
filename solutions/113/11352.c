/* 11352
 * Crazy King
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_STRING  (MAX_N + 2)
#define MAX_DIM     (MAX_N * MAX_N)
#define INFINITY    (1 << 30)

#define IN(v,lim)   ((v) >= 0 && (v) < (lim))
#define DIST(p)     (distance[(p).row][(p).col])
#define MAP(p)      (map[(p).row][(p).col])

#define KNIGHT  'Z'
#define FREE    '.'
#define BLOCKED '#'
#define ORIGIN  'A'
#define DESTINY 'B'

typedef struct {
    int row, col;
} point_t;

char map[MAX_N][MAX_STRING];
int distance[MAX_N][MAX_N];
int rows, columns;
point_t origin;

/* Read map and block all passages captured by knights */
void read_map() {
    int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int r, c, k;
    assert(scanf("%d %d", &rows, &columns) != EOF);
    for (r = 0; r < rows; r++) {
        assert(scanf(" %s", map[r]) != EOF);
    }
    for (r = 0; r < rows; r++) {
        for (c = 0; c < columns; c++) {
            distance[r][c] = INFINITY;
            if (map[r][c] == ORIGIN) origin.row = r, origin.col = c;
            else if (map[r][c] == KNIGHT) {
                for (k = 0; k < 8; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (IN(nr, rows) && IN(nc, columns) && map[nr][nc] == FREE) {
                        map[nr][nc] = BLOCKED;
                    }
                }
            }
        }
    }
}

/* Find minimum distance */
int get_minimum_distance() {
    int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    point_t queue[MAX_DIM], next;
    int k, front, rear;
    DIST(origin) = 0;
    queue[0] = origin, front = 0, rear = 1;
    while (front < rear) {
        point_t point = queue[front++];
        int dist = DIST(point) + 1;
        for (k = 0; k < 8; k++) {
            next.row = point.row + dr[k], next.col = point.col + dc[k];
            if (!IN(next.row, rows) || !IN(next.col, columns)) continue;
            if (MAP(next) == DESTINY) return dist;
            if (MAP(next) != FREE) continue;
            if (DIST(next) == INFINITY) {
                queue[rear++] = next;
                DIST(next) = dist;
            }
        }
    }
    return -1;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int distance;
        read_map();
        distance = get_minimum_distance();
        if (distance < 0) printf("King Peter, you can't go now!\n");
        else printf("Minimal possible length of a trip is %d\n", distance);
    }
    return EXIT_SUCCESS;
}
