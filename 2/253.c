/* 253
 * Cube painting
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_ROTATIONS   24
#define NUM_FACES       6
#define MAX_CUBE_STR    (NUM_FACES + 2)
#define MAX_STRING      (2 * MAX_CUBE_STR)

char rotation[NUM_ROTATIONS][MAX_CUBE_STR] = {
    "123456", "142536", "154326", "135246",
    "263415", "246135", "214365", "231645",
    "326154", "312564", "351624", "365214",
    "421653", "462513", "456123", "415263",
    "541632", "564312", "536142", "513462",
    "624351", "645231", "653421", "632541"};

/* Whether on cube is a rotation of the other */
int is_rotation(char *cube, char *other) {
    int i, r, ref, check;
    for (r = 0; r < NUM_ROTATIONS; r++) {
        for (check = 1, i = 0; check && i < NUM_FACES; i++) {
            ref = (rotation[r][i] - '1') % NUM_FACES;
            check = cube[i] == other[ref];
        }
        if (check) {
            return 1;
        }
    }
    return 0;
}

/* Main function */
int main() {
    char input[MAX_STRING];
    while (scanf(" %s", input) != EOF) {
        printf("%s\n", is_rotation(input, input + NUM_FACES) ? "TRUE" : "FALSE");
    }
    return 0;
}
