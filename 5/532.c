/* 532
 * Dungeon Master
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     30
#define MAX_CELLS   (MAX_DIM * MAX_DIM * MAX_DIM)
#define MAX_MOVES   6
#define MAX_STRING  (MAX_DIM + 2)
#define WALL        '#'
#define EXIT        'E'
#define START       'S'

typedef struct {
    int x, y, z;
} cell_t, *cell_p;

cell_t move[MAX_MOVES] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
char map[MAX_DIM][MAX_DIM][MAX_STRING];
int rows, columns, levels;

#define IN(x,l)         ((x) >= 0 && (x) < (l))
#define MAP(c)          (map[(c).z][(c).y][(c).x])
#define SETP(c,a,b,p)   (c).p = (a).p + (b).p
#define SET(c,a,b)      SETP(c,a,b,x); SETP(c,a,b,y); SETP(c,a,b,z)

/* Find shortest path to exit from start */
int find_path(cell_t start) {
    struct {
        cell_t cell;
        int distance;
    } *current, queue[MAX_CELLS];
    int i, front, rear;

    queue[0].cell = start, queue[0].distance = 0;
    front = 0, rear = 1;
    MAP(start) = WALL;
    while (front < rear) {
        current = &queue[front++];
        for (i = 0; i < MAX_MOVES; i++) {
            SET(start, current->cell, move[i]);
            if (IN(start.x, columns) && IN(start.y, rows) && IN(start.z, levels) 
                    && MAP(start) != WALL) {
                if (MAP(start) == EXIT) {
                    return current->distance + 1;
                }
                queue[rear].cell = start, queue[rear].distance = current->distance + 1;
                MAP(start) = WALL;
                rear++;
            }
        }
    }
    return -1;
}

/* Main function */
int main() {
    while (scanf(" %d %d %d", &levels, &rows, &columns) != EOF && levels > 0) {
        cell_t start;
        int y, z;
        char *p;
        for (z = 0; z < levels; z++) {
            for (y = 0; y < rows; y++) {
                assert(scanf(" %s", map[z][y]) != EOF);
                p = strchr(map[z][y], START);
                if (p != NULL) {
                    start.z = z, start.y = y, start.x = p - map[z][y];
                }
            }
        }
#if 0
        {
            fprintf(stderr, "START: Z=%d Y=%d X=%d\n", start.z, start.y, start.x);
            for (z = 0; z < levels; z++) {
                fprintf(stderr, "MAP Z=%d\n", z);
                for (y = 0; y < rows; y++) {
                    fprintf(stderr, "Y=%2d   >%s<\n", y, map[z][y]);
                }
            }
        }
#endif
        z = find_path(start);
        if (z < 0) {
            printf("Trapped!\n");
        }
        else {
            printf("Escaped in %d minute(s).\n", z);
        }
    }
    return 0;
}
