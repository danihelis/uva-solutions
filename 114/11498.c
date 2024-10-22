/* 11498
 * Division of Nlogonia
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    int x, y;
} point_t;

/* Main function */
int main() {
    point_t center, input;
    int tests;
    while (scanf("%d", &tests) != EOF) {
        if (tests == 0) {
            break;
        }
        assert(scanf("%d %d", &center.x, &center.y) != EOF);
        for (; tests > 0; tests--) {
            assert(scanf("%d %d", &input.x, &input.y) != EOF);
            if (input.x == center.x || input.y == center.y) {
                printf("divisa\n");
            }
            else {
                printf("%c%c\n", (input.y > center.y ? 'N' : 'S'), 
                        (input.x > center.x ? 'E' : 'O'));
            }
        }
    }
    return 0;
}
