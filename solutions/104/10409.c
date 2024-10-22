/* 10409
 * Die Game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef enum {
    TOP,
    NORTH,
    BOTTOM,
    SOUTH,
    EAST,
    WEST
} side_t;

side_t vertical[4] = {NORTH, TOP, SOUTH, BOTTOM},
       horizontal[4] = {WEST, TOP, EAST, BOTTOM};

/* Shift */
void shift(int die[], side_t side[], int dir) {
    int i, back;
    back = die[dir == 1 ? side[3] : side[0]];
    for (i = 0; i < 4; i++)
        die[side[dir == 1 ? 3 - i : i]] = i == 3 ? back :
            die[side[dir == 1 ? 2 - i : i + 1]];
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int die[6] = {1, 2, 6, 5, 4, 3};
        for (; n > 0; n--) {
            char dir;
            assert(scanf(" %c%*s", &dir) != EOF);
            switch (dir) {
                case 'n': shift(die, vertical, -1); break;
                case 's': shift(die, vertical, 1); break;
                case 'w': shift(die, horizontal, -1); break;
                case 'e': shift(die, horizontal, 1); break;
            }
        }
        printf("%d\n", die[TOP]);
    }
    return EXIT_SUCCESS;
}
