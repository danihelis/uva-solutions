/**
 * 118
 * Mutant Flatworld Explorers
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_DIM  51
#define MAX_INST 101
#define MAX_DIR  4

char direction[5] = "SWNE";
char scent[MAX_DIM][MAX_DIM];
int max_x, max_y;
int x, y, dir;
char instruction[MAX_INST];

/* Simulate a series of instructions */
int simulate() {
    char *i;
    for (i = instruction; *i != '\0'; i++) {
        int nx, ny, dir_change = 0;
        switch (*i) {
            case 'R':
                dir_change = 2;
            case 'L':
                dir_change -= 1;
                dir = (dir + dir_change + MAX_DIR) % MAX_DIR;
                break;
            case 'F':
                nx = x + (direction[dir] == 'E' ? 1 : (direction[dir] == 'W' ? -1 : 0));
                ny = y + (direction[dir] == 'N' ? 1 : (direction[dir] == 'S' ? -1 : 0));
                if (nx < 0 || nx > max_x || ny < 0 || ny > max_y) {
                    if (!scent[x][y]) { /* fall off the map */
                        scent[x][y] = 1;
                        return 0;
                    }
                }
                else {
                    x = nx;
                    y = ny;
                }
                break;
            default:
                assert(*i);
        }
    }
    return 1;
}

/* Main */
int main() {
    char robot_dir;
    int safe;

    memset(scent, 0, (MAX_DIM * MAX_DIM) * sizeof (char));
    scanf("%d %d", &max_x, &max_y);

    while (scanf("%d %d %c", &x, &y, &robot_dir) == 3) {
        dir = strchr(direction, robot_dir) - direction;
        assert(dir >= 0 && dir <= MAX_DIR);
        scanf("%s", instruction);
        safe = simulate();
        printf("%d %d %c", x, y, direction[dir]);
        if (!safe) {
            printf(" LOST");
        }
        printf("\n");
    }
    return 0;
}

