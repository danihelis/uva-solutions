/* 11624
 * Fire!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LEN     1000
#define MAX_STRING  (MAX_LEN + 2)
#define MAX_DIM     (MAX_LEN * MAX_LEN)

#define WALL    '#'
#define PASSAGE '.'
#define JOHN    'J'
#define FIRE    'F'

#define DIRS    4

typedef struct {
    short row, col;
} pos_t;

char map[MAX_DIM][MAX_STRING];
int rows, cols;

/* Find exit for John */
#define IN(x, m)    ((x) >= 0 && (x) < (m))
int find_exit() {
    static int dr[DIRS] = {-1, 0, 1, 0}, dc[DIRS] = {0, 1, 0, -1};
    pos_t john[MAX_DIM], fire[MAX_DIM];
    int front_j, rear_j, front_f, rear_f;
    short r, c, i;
    int time;

    /* Fill queue with John's and fires' positions */
    for (front_j = rear_j = front_f = rear_f = 0, r = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            if (map[r][c] == JOHN) {
                john[rear_j].row = r, john[rear_j].col = c;
                rear_j++;
            }
            else if (map[r][c] == FIRE) {
                fire[rear_f].row = r, fire[rear_f].col = c;
                rear_f++;
            }

    /* Simulates each unit of time */
    for (time = 1; front_j < rear_j; time++) {
        pos_t new;
        int last;

        /* Spread John */
        last = rear_j;
        while (front_j < last) {
            pos_t cur = john[front_j++];
            if (map[cur.row][cur.col] != JOHN)
                continue; /* John was engulfed by fire! */
            if (cur.row == 0 || cur.row == rows - 1 || cur.col == 0 ||
                    cur.col == cols - 1)
                return time;
            for (i = 0; i < DIRS; i++) {
                new.row = cur.row + dr[i], new.col = cur.col + dc[i];
                if (map[new.row][new.col] == PASSAGE) {
                    map[new.row][new.col] = JOHN;
                    john[rear_j++] = new;
                }
            }
        }
        
        /* Spread fire */
        last = rear_f;
        while (front_f < last) {
            pos_t cur = fire[front_f++];
            for (i = 0; i < DIRS; i++) {
                new.row = cur.row + dr[i], new.col = cur.col + dc[i];
                if (IN(new.row, rows) && IN(new.col, cols) &&
                        (map[new.row][new.col] == PASSAGE || 
                         map[new.row][new.col] == JOHN)) {
                    map[new.row][new.col] = FIRE;
                    fire[rear_f++] = new;
                }
            }
        }
    }
    return -1;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, time;
        assert(scanf("%d %d", &rows, &cols) == 2);
        for (i = 0; i < rows; i++)
            assert(scanf(" %s", map[i]) == 1);
        time = find_exit();
        if (time > 0)
            printf("%d\n", time);
        else
            puts("IMPOSSIBLE");
    }
    return EXIT_SUCCESS;
}
