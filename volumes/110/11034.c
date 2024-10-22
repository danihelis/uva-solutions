/* 11034
 * Ferry Loading IV
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CARS 100000
#define MAX_STRING 10
#define NUM_SIDES 2

typedef enum {
    LEFT = 0,
    RIGHT
} side_t;

typedef struct {
    int length[MAX_CARS];
    int front, end;
} queue_t;

queue_t queue[NUM_SIDES];

#define ENQUEUE(q, x) queue[q].length[queue[q].end++] = (x)
#define DEQUEUE(q) queue[q].length[queue[q].front++]
#define FIRST(q)  queue[q].length[queue[q].front]
#define EMPTY(q) (queue[q].front >= queue[q].end)
#define INITIALIZE(q) queue[q].front = queue[q].end = 0

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        int i, space, num_cars, travels;
        side_t side;
        assert(scanf("%d %d", &space, &num_cars) != EOF);
        space *= 100;
        INITIALIZE(LEFT), INITIALIZE(RIGHT);
        for (i = 0; i < num_cars; i++) {
            char where[MAX_STRING];
            int length;
            assert(scanf("%d %s", &length, where) != EOF);
            assert(length <= space);
            ENQUEUE((*where == 'l' ? LEFT : RIGHT), length);
        }
        travels = 0, side = LEFT;
        while (!EMPTY(LEFT) || !EMPTY(RIGHT)) {
            int left = space;
            while (!EMPTY(side) && FIRST(side) < left) {
                left -= DEQUEUE(side);
            }
            travels++;
            side = 1 - side;
        }
        printf("%d\n", travels);
    }
    return 0;
}
