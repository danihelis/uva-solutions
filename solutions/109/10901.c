/* 10901
 * Ferry Loading III
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_QUEUE 10000
#define MAX_STRING 10
#define NUM_SIDES 2

typedef enum {
    LEFT = 0,
    RIGHT = 1
} side_t;

typedef struct {
    int start, unload;
} car_t, *car_p;

typedef struct {
    car_p car[MAX_QUEUE];
    int front, end;
} queue_t;

car_t car[MAX_QUEUE];
queue_t queue[NUM_SIDES];
car_p ferry[MAX_QUEUE];

#define ENQUEUE(q, x) queue[q].car[queue[q].end++] = (x)
#define FIRST(q) (queue[q].car[queue[q].front])
#define DEQUEUE(q) (queue[q].car[queue[q].front++])
#define EMPTY(q) (queue[q].front >= queue[q].end)

/* Main function */
int main() {
    int tests, travel, ferry_size, num_cars;
    side_t side;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        int i, timestamp;
        assert(scanf("%d %d %d", &ferry_size, &travel, &num_cars) != EOF);
        for (i = 0; i < NUM_SIDES; i++) {
            queue[i].front = 0, queue[i].end = 0;
        }
        for (i = 0; i < num_cars; i++) {
            char side[MAX_STRING];
            assert(scanf("%d %s", &car[i].start, side) != EOF);
            car[i].unload = -1;
            ENQUEUE((*side == 'l' ? LEFT : RIGHT), &car[i]);
        }

        /* Simulate ferry travel */
        side = LEFT, timestamp = 0;
        while (!EMPTY(LEFT) || !EMPTY(RIGHT)) {
            int earlier = -1, in_ferry;
            side_t earlier_side = 0;
            for (i = 0; i < NUM_SIDES; i++) {
                if (!EMPTY(i) && (earlier == -1 || earlier > FIRST(i)->start)) {
                    earlier = FIRST(i)->start;
                    earlier_side = i;
                }
            }
            if (timestamp < earlier) {
                timestamp = earlier + (earlier_side == side ? 0 : travel);
                side = earlier_side;
            }
            else if (EMPTY(side)) {
                timestamp += travel;
                side = 1 - side;
            }
            assert(!EMPTY(side));

            in_ferry = 0;
            while (in_ferry < ferry_size && !EMPTY(side) && FIRST(side)->start <= timestamp) {
                in_ferry++;
                DEQUEUE(side)->unload = timestamp + travel;
            }
            timestamp += travel;
            side = 1 - side;
        }

        for (i = 0; i < num_cars; i++) {
            assert(car[i].unload >= 0);
            printf("%d\n", car[i].unload);
        }
        printf("%s", tests > 1 ? "\n" : "");
    }
    return 0;
}
