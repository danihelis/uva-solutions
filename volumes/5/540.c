/* 540
 * Team Queue
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TEAMS       1000
#define MAX_MEMBERS     1000
#define MAX_PEOPLE      (MAX_TEAMS * MAX_MEMBERS)

typedef struct {
    int data[MAX_MEMBERS], front, rear;
} tqueue_t;

typedef struct {
    tqueue_t *data[MAX_TEAMS];
    int front, rear;
} queue_t;

int team[MAX_PEOPLE], num_teams;
tqueue_t team_queue[MAX_TEAMS];
queue_t queue;

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_teams) == 1 && num_teams > 0) {
        int t, number, size;
        tqueue_t *tq;
        char command;
        for (t = 0; t < num_teams; t++) {
            assert(scanf("%d", &size) == 1);
            for (; size > 0; size--) {
                assert(scanf("%d", &number) == 1);
                team[number] = t;
            }
            team_queue[t].front = team_queue[t].rear = 0;
        }
        queue.front = queue.rear = 0;
        printf("Scenario #%d\n", ++test);
        while (scanf(" %c%*s", &command) == 1 && command != 'S') {
            if (command == 'D') {
                assert(queue.front != queue.rear);
                tq = queue.data[queue.front];
                assert(tq->front != tq->rear);
                printf("%d\n", tq->data[tq->front]);
                tq->front = (tq->front + 1) % MAX_MEMBERS;
                if (tq->front == tq->rear) {
                    queue.front = (queue.front + 1) % MAX_TEAMS;
                    tq = queue.data[queue.front];
                }
            }
            else {
                assert(scanf("%d", &number) == 1);
                tq = &team_queue[team[number]];
                if (tq->front == tq->rear) {
                    queue.data[queue.rear] = tq;
                    queue.rear = (queue.rear + 1) % MAX_TEAMS;
                }
                tq->data[tq->rear] = number;
                tq->rear = (tq->rear + 1) % MAX_MEMBERS;
            }
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
