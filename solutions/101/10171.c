/* 10171
 * Meeting Prof. Miguel...
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PLACES  26
#define MAX_HEAP    (MAX_PLACES * MAX_PLACES)

#define PARENT(x)   (((x) - 1) / 2)
#define CHILD(x)    (2 * (x) + 1)
#define SWAP(x,y)   do { \
        item_t _swap = heap[x]; \
        heap[x] = heap[y]; \
        heap[y] = _swap; \
        x = y; \
    } while (0)

typedef enum {
    YOUNG = 0,
    MATURE = 1
} type_t;

typedef struct {
    int road[2][MAX_PLACES];
    int cost[2], visited, total;
} place_t;

typedef struct {
    int place, cost;
} item_t;

place_t place[MAX_PLACES];
item_t heap[MAX_HEAP];
int heap_size;

/* Insert into heap */
void insert_heap(int place, int cost) {
    int index = heap_size;
    heap[heap_size].place = place, heap[heap_size].cost = cost;
    heap_size++;
    while (index > 0 && heap[PARENT(index)].cost > heap[index].cost)
        SWAP(index, PARENT(index));
}

/* Remove from heap */
item_t remove_heap() {
    int index, child;
    item_t minimum = heap[0];
    heap[0] = heap[--heap_size];
    index = 0;
    while ((child = CHILD(index)) < heap_size) {
        if (child < heap_size + 1 && 
                heap[child].cost > heap[child + 1].cost)
            child++;
        if (heap[child].cost > heap[index].cost)
            break;
        else
            SWAP(index, child);
    }
    return minimum;
}

/* Find distance from start to all places */
void find_distance(int start, type_t type) {
    int i;
    for (i = 0; i < MAX_PLACES; i++)
        place[i].visited = 0;
    heap_size = 0;
    insert_heap(start, 0);
    while (heap_size > 0) {
        item_t cur = remove_heap();
        if (place[cur.place].visited)
            continue;
        place[cur.place].visited = 1;
        place[cur.place].cost[type] = cur.cost;
        for (i = 0; i < MAX_PLACES; i++) {
            int link = place[cur.place].road[type][i];
            if (link >= 0 && !place[i].visited)
                insert_heap(i, link + cur.cost);
        }
    }
}

/* Find best meeting location */
void find_location(int young, int mature) {
    int i, best;
    for (i = 0; i < MAX_PLACES; i++) {
        memset(place[i].cost, -1, sizeof (place[i].cost));
        place[i].total = -1;
    }
    find_distance(young, YOUNG);
    find_distance(mature, MATURE);
   
    for (i = 0, best = -1; i < MAX_PLACES; i++)
        if (place[i].cost[YOUNG] >= 0 && place[i].cost[MATURE] >= 0) {
            place[i].total = place[i].cost[YOUNG] + place[i].cost[MATURE];
            if (best == -1 || place[i].total < best)
                best = place[i].total;
        }
    if (best == -1)
        printf("You will never meet.\n");
    else {
        printf("%d", best);
        for (i = 0; i < MAX_PLACES; i++) 
            if (place[i].total == best)
                printf(" %c", i + 'A');
        printf("\n");
    }
}

/* Add a road */
void add_road(type_t type, char bidirection, int p1, int p2, int cost) {
    if (place[p1].road[type][p2] == -1 || place[p1].road[type][p2] > cost)
        place[p1].road[type][p2] = cost;
    if (bidirection)
        add_road(type, 0, p2, p1, cost);
}

/* Main function */
int main() {
    int num_roads;
    while (scanf("%d", &num_roads) != EOF && num_roads > 0) {
        int i;
        char young, mature;
        for (i = 0; i < MAX_PLACES; i++)
            memset(place[i].road, -1, sizeof (place[i].road));
        for (; num_roads > 0; num_roads--) {
            char type, dir, p1, p2;
            int cost;
            assert(scanf(" %c %c %c %c %d", &type, &dir, &p1, &p2, &cost)
                    != EOF);
            add_road(type == 'Y' ? YOUNG : MATURE, dir == 'B',
                    p1 - 'A', p2 - 'A', cost);
        }
        assert(scanf(" %c %c", &young, &mature) != EOF);
        find_location(young - 'A', mature - 'A');
    }
    return EXIT_SUCCESS;
}
