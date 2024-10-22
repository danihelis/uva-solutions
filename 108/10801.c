/* 10801
 * Lift Hopping
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_FLOORS      100
#define MAX_ELEVATORS   15
#define CHANGE_COST     60

#define HAS_ELEV(floor, elev)   (has_elevator[floor] & (1 << elev))

#define MAX_HEAP        1000000

typedef struct {
    int floor, elevator, time;
} step_t;

int has_elevator[MAX_FLOORS];
int floors[MAX_ELEVATORS][MAX_FLOORS];
int num_floors[MAX_ELEVATORS], cost[MAX_ELEVATORS];
int num_elevators, destiny;

step_t heap[MAX_HEAP];
int heap_size;

#define ABS_DIFF(x, y)  ((x) < (y) ? (y) - (x) : (x) - (y))
#define PARENT(i)       (((i) - 1) / 2)
#define CHILD(i)        ((i) * 2 + 1)
#define SWAP(i, j)      do { \
        step_t swap = heap[i]; \
        heap[i] = heap[j]; \
        heap[j] = swap; \
    } while (0)

/* Insert into heap */
void insert_heap(step_t v) {
    int index = heap_size++;
    assert(heap_size <= MAX_HEAP);
    heap[index] = v;
    while (heap[PARENT(index)].time > heap[index].time) {
        SWAP(PARENT(index), index);
        index = PARENT(index);
    }
}

/* Remove from heap */
step_t remove_heap() {
    step_t minimum = heap[0];
    int index = 0, child;
    heap[0] = heap[--heap_size];
    while ((child = CHILD(index)) < heap_size) {
        if (child + 1 < heap_size && heap[child].time > heap[child + 1].time)
            child++;
        if (heap[child].time < heap[index].time) {
            SWAP(child, index);
            index = child;
        } else
            break;
    }
    return minimum;
}

/* Find shortest trip (Dijkstra) */
int find_shortest_trip() {
    step_t cur, next, first = {0, -1, 0};
    char visited[MAX_FLOORS];
    int e, i;

    memset(visited, 0, MAX_FLOORS);
    heap_size = 0;
    insert_heap(first);

    while (heap_size > 0) {
        cur = remove_heap();
        if (visited[cur.floor])
            continue;
        visited[cur.floor] = 1;
        if (cur.floor == destiny)
            return cur.time;
        for (e = 0; e < num_elevators; e++)
            if (e != cur.elevator && HAS_ELEV(cur.floor, e)) {
                for (i = 0; i < num_floors[e]; i++)
                    if (!visited[floors[e][i]]) {
                        next.floor = floors[e][i];
                        next.elevator = e; 
                        next.time = cur.time + 
                            (cur.elevator == -1 ? 0 : CHANGE_COST) + 
                            cost[e] * ABS_DIFF(next.floor, cur.floor);
                        insert_heap(next);
                    }
            }
    }
    return -1;
}

/* Main function */
#define MAX_STRING  1000
#define READ(line)  (fgets(line, MAX_STRING, stdin) != NULL)
int main() {
    char line[MAX_STRING], *p;
    while (READ(line) && 
            sscanf(line, "%d %d", &num_elevators, &destiny) == 2) {
        int i, result;
        /*assert(num_elevators < MAX_ELEVATORS);*/
        memset(has_elevator, 0, MAX_FLOORS * sizeof (int));
        assert(READ(line));
        for (i = 0, p = strtok(line, " "); i < num_elevators; 
                i++, p = strtok(NULL, " ")) {
            assert(p != NULL);
            cost[i] = atoi(p);
        }
        for (i = 0; i < num_elevators; i++) {
            assert(READ(line));
            for (num_floors[i] = 0, p = strtok(line, " "); p != NULL; 
                    num_floors[i]++, p = strtok(NULL, " ")) {
                int f = floors[i][num_floors[i]] = atoi(p);
                has_elevator[f] |= 1 << i;
            }
        }
        result = find_shortest_trip();
        if (result < 0)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", result);
    }
    return EXIT_SUCCESS;
}
