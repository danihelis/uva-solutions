/* 11244
 * Counting Stars
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_SIZE    (MAX_DIM * MAX_DIM)
#define NUM_DIRS    8

#define IN(x,y)     ((x) >= 0 && (x) < rows && (y) >= 0 && (y) < cols)

char map[MAX_DIM][MAX_DIM + 2];
int rows, cols;

/* Flood fill */
int flood_fill(int r, int c) {
    struct {
        int r, c;
    } queue[MAX_SIZE], cur, next;
    int i, front, rear, count;
    int dr[NUM_DIRS] = {-1, -1, 0, 1, 1, 1, 0, -1},
        dc[NUM_DIRS] = {0, 1, 1, 1, 0, -1, -1, -1};

    queue[0].r = r, queue[0].c = c, front = 0, rear = 1, count = 0;
    map[r][c] = '.';
    while (front < rear) {
        cur = queue[front++];
        count++;
        for (i = 0; i < NUM_DIRS; i++) {
            next.r = cur.r + dr[i], next.c = cur.c + dc[i];
            if (IN(next.r, next.c) && map[next.r][next.c] == '*') {
                map[next.r][next.c] = '.';
                queue[rear++] = next;
            }
        }
    }
    return count;
}

/* Main function */
int main() {
    while (scanf("%d %d", &rows, &cols) != EOF && rows > 0) {
        int r, c, stars;
        for (r = 0; r < rows; r++)
            assert(scanf(" %s", map[r]) == 1);
        for (r = stars = 0; r < rows; r++)
            for (c = 0; c < cols; c++)
                if (map[r][c] == '*' && flood_fill(r, c) == 1)
                    stars++;
        printf("%d\n", stars);
    }
    return EXIT_SUCCESS;
}
