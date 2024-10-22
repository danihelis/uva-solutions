/* 11906
 * Knight in a War Grid
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
#define MAX_DIR     4

typedef struct {
    int r, c;
} point_t;

char map[MAX_DIM][MAX_DIM], visited[MAX_DIM][MAX_DIM];
int rows, cols, odds, evens;
point_t move[2];

/* Visit all squares */
#define IN(p)   ((p).r >= 0 && (p).r < rows && (p).c >= 0 && (p).c < cols)
void visit() {
    point_t queue[MAX_SIZE], cur, new;
    point_t d[MAX_DIR] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int i, k, count, front, rear, rep;

    odds = evens = 0;
    rep = move[0].r == move[1].r && move[0].c == move[1].c ? 1 : 2;

    queue[0].r = queue[0].c = 0;
    front = 0, rear = 1;
    visited[0][0] = 1;

    while (front < rear) {
        cur = queue[front++];
        for (k = count = 0; k < rep; k++) 
            for (i = 0; i < MAX_DIR; i++) {
                if ((move[k].r == 0 && i >= 2) || 
                        (move[k].c == 0 && i % 2 == 1))
                    continue;
                new.r = cur.r + move[k].r * d[i].r;
                new.c = cur.c + move[k].c * d[i].c;
                if (IN(new) && map[new.r][new.c]) {
                    count++;
                    if (!visited[new.r][new.c]) {
                        queue[rear++] = new;
                        visited[new.r][new.c] = 1;
                    }
                }
            }
        odds += count % 2 == 1 ? 1 : 0;
        evens += count % 2 == 0 ? 1 : 0;
    }
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, j, w;
        assert(scanf("%d %d %d %d", &rows, &cols, &i, &j) == 4);
        move[0].r = i, move[0].c = j;
        move[1].r = j, move[1].c = i;
        for (i = 0; i < rows; i++)
            for (j = 0; j < cols; j++)
                map[i][j] = 1, visited[i][j] = 0;
        assert(scanf("%d", &w) == 1);
        for (; w > 0; w--) {
            assert(scanf("%d %d", &i, &j) == 2);
            map[i][j] = 0;
        }
        visit();
        printf("Case %d: %d %d\n", test, evens, odds);
    }
    return EXIT_SUCCESS;
}
