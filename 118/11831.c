/* 11831
 * Sticker Collector Robot
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_STRING  (MAX_DIM + 2)

#define NUM_DIRS    4

#define EMPTY       '.'
#define STICK       '*'
#define WALL        '#'

typedef enum {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    UNDEFINED = 4
} dir_t;

int drow[NUM_DIRS] = {-1, 0, 1, 0};
int dcol[NUM_DIRS] = {0, 1, 0, -1};
char direction[] = "NLSO";

char map[MAX_DIM][MAX_STRING];
int width, height, num_inst;

/* Count how many sticks robo collects */
int get_sticks() {
    int i, j, row, col, sticks;
    dir_t dir;

    for (i = 0, dir = UNDEFINED, row = -1, col = -1; i < height; i++) {
        assert(scanf(" %s", map[i]) != EOF);
        for (j = 0; dir == UNDEFINED && j < width; j++) {
            char *pos = strchr(direction, map[i][j]);
            if (pos != NULL) {
                dir = pos - direction;
                row = i, col = j;
            }
        }
    }
    assert(dir != UNDEFINED);

    for (sticks = 0; num_inst > 0; num_inst--) {
        char inst;
        assert(scanf(" %c", &inst) != EOF);
        switch (inst) {
            case 'D':
                dir = (dir + 1) % NUM_DIRS;
                break;
            case 'E':
                dir = (dir + NUM_DIRS - 1) % NUM_DIRS;
                break;
            case 'F':
                i = row + drow[dir], j = col + dcol[dir];
                if (i < 0 || i >= height || j < 0 || j >= width ||
                        map[i][j] == WALL)
                    break;
                sticks += map[i][j] == STICK ? 1 : 0;
                map[i][j] = EMPTY;
                row = i, col = j;
                break;
            default:
                assert(NULL);
        }
    }
    return sticks;
}

/* Main function */
int main() {
    while (scanf("%d %d %d", &height, &width, &num_inst) != EOF &&
            height > 0)
        printf("%d\n", get_sticks());
    return EXIT_SUCCESS;
}
