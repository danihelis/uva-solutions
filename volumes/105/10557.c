/* 10557
 * XYZZY
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ROOMS   100
#define INFINITY    9999999

typedef struct {
    int edge[MAX_ROOMS], num_edges;
    int cost, last_entry, stacked, queued;
} room_t;

room_t room[MAX_ROOMS], *last;
int num_rooms;

/* Find a direct exit from the current room, marking energy as infinite */
int find_exit(room_t *current) {
    room_t *queue[MAX_ROOMS];
    int i, front, rear;
    queue[0] = current, front = 0, rear = 1;
    current->queued = 1;
    while (front < rear) {
        current = queue[front++];
        if (current == last)
            return 1;
        current->last_entry = INFINITY;
        for (i = 0; i < current->num_edges; i++) {
            room_t *next = &room[current->edge[i]];
            if (!next->queued) {
                next->queued = 1;
                queue[rear++] = next;
            }
        }
    }
    return 0;
}

/* Find a route to exit observing energy levels */
int find_route(room_t *current, int energy) {
    int i, found;
    if (current == last)
        return 1;
    current->stacked = 1;
    current->last_entry = energy;
    energy += current->cost;
    for (i = 0, found = 0; !found && i < current->num_edges; i++) {
        room_t *next = &room[current->edge[i]];
        if (energy > next->last_entry)
            found = next->stacked ? find_exit(next) : 
                    find_route(next, energy);
    }
    current->stacked = 0;
    return found;
}

/* Main function */
int main() {
    while (scanf("%d", &num_rooms) != EOF && num_rooms != -1) {
        int i, e;
        for (i = 0; i < num_rooms; i++) {
            room_t *r = &room[i];
            assert(scanf("%d %d", &r->cost, &r->num_edges) != EOF);
            for (e = 0; e < r->num_edges; e++) {
                assert(scanf("%d", &r->edge[e]) != EOF);
                r->edge[e]--;
            }
            r->stacked = r->queued = r->last_entry = 0;
        }
        last = &room[num_rooms - 1];
        printf("%s\n", find_route(&room[0], 100) ? "winnable" : "hopeless");
    }
    return EXIT_SUCCESS;
}
