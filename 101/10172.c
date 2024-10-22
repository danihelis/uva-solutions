/* 10172
 * The Lonesome Cargo Distributor
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STATIONS    100
#define MAX_QUEUE       101
#define MAX_STACK       100

#define TIME_MOVE       2
#define TIME_STACK      1

typedef struct {
    int item[MAX_QUEUE];
    int first, last;
} queue_t;

int queue_size, stack_size;
queue_t queue[MAX_STATIONS];
int stack[MAX_STACK], top;

#define QUEUE_SIZE(q)   (((q)->last - (q)->first + MAX_QUEUE) % MAX_QUEUE)

#define QUEUE_EMPTY(q)  ((q)->last == (q)->first)

#define QUEUE_FULL(q)   (QUEUE_SIZE(q) == queue_size)

#define ENQUEUE(q, i)   do { \
        (q)->item[(q)->last] = i; \
        (q)->last = ((q)->last + 1) % MAX_QUEUE; \
    } while (0);

#define DEQUEUE(q, i) do { \
        i = (q)->item[(q)->first]; \
        (q)->first = ((q)->first + 1) % MAX_QUEUE; \
    } while (0);

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j, time, total, station, num_stations;
        assert(scanf("%d %d %d", &num_stations, &stack_size, &queue_size) 
                != EOF);
        for (i = 0, total = 0; i < num_stations; i++) {
            assert(scanf("%d", &queue[i].last) != EOF);
            queue[i].first = 0;
            for (j = 0; j < queue[i].last; j++) {
                assert(scanf("%d", &queue[i].item[j]) != EOF);
            }
            total += queue[i].last;
        }
        time = 0, station = -1, top = 0;
        while (total > 0) {
            queue_t *q;
            time += station >= 0 ? TIME_MOVE : 0;
            station = (station + 1) % num_stations;
            q = &queue[station];
            while (top > 0) {
                if (stack[top - 1] == station + 1 || !QUEUE_FULL(q)) {
                    if (stack[top - 1] == station + 1) {
                        total--;
                    }
                    else {
                        ENQUEUE(q, stack[top - 1]);
                    }
                    time += TIME_STACK;
                    top--;
                }
                else break;
            }
            while (top < stack_size && !QUEUE_EMPTY(q)) {
                DEQUEUE(q, stack[top]);
                top++;
                time += TIME_STACK;
            }
        }
        printf("%d\n", time);
    }
    return 0;
}
