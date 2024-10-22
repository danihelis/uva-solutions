/* 587
 * There's treasure everywhere!
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      300
#define MAX_DIRECTIONS  8
#define DIAGONAL        0.7071067811865475

typedef enum {
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST,
    NONE
} direction_t;

struct {
    double x, y;
} move[MAX_DIRECTIONS] = {
    {0, 1}, {DIAGONAL, DIAGONAL}, {1, 0}, {DIAGONAL, -DIAGONAL},
    {0, -1}, {-DIAGONAL, -DIAGONAL}, {-1, 0}, {-DIAGONAL, DIAGONAL}};

/* Main function */
int main() {
    char line[MAX_STRING];
    int map = 0;
    while (scanf(" %[^\n]", line) != EOF && strcmp(line, "END") != 0) {
        double x = 0, y = 0, dist;
        int step;
        direction_t dir;
        char *p = line;
        while (*p != '.' && *p != 0) {
            step = 0;
            while (isdigit(*p) && *p != 0) {
                step = step * 10 + *p - '0';
                p++;
            }
            dir = NONE;
            while (isupper(*p) && *p != 0) {
                switch (*p) {
                    case 'N': dir = NORTH; break;
                    case 'S': dir = SOUTH; break;
                    case 'E': dir = dir == NORTH ? NORTHEAST : dir == SOUTH ? SOUTHEAST : EAST; 
                              break;
                    case 'W': dir = dir == NORTH ? NORTHWEST : dir == SOUTH ? SOUTHWEST : WEST;
                }
                p++;
            }
            x += step * move[(int) dir].x, y += step * move[(int) dir].y;
            if (*p == 0) {
                break;
            }
            p++;
        }
        dist = sqrt(x * x + y * y);
        printf("Map #%d\nThe treasure is located at (%.3f,%.3f).\n"
                "The distance to the treasure is %.3f.\n\n", ++map, x, y, dist);
    }
    return 0;
}
