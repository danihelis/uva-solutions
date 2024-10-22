/* 1203
 * Argus
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_HEAP    1000
#define PARENT(i)   (((i) - 1) / 2)
#define CHILD(i)    ((i) * 2 + 1)
#define LOWER(a,b)  ((heap[a].time != heap[b].time) ? \
                        (heap[a].time < heap[b].time) : \
                        (heap[a].key < heap[b].key))
#define SWAP(a,b)   do { \
        elem_t swap = heap[a]; \
        heap[a] = heap[b]; \
        heap[b] = swap; \
    } while (0)

typedef struct {
    int key, period, time;
} elem_t;

elem_t heap[MAX_HEAP];
int size;

/* Move up */
void move_up(int i) {
    int parent = PARENT(i);
    while (i > 0 && LOWER(i, parent)) {
        SWAP(i, parent);
        i = parent;
        parent = PARENT(i);
    }
}

/* Move down */
void move_down() {
    int i = 0, child = CHILD(0);
    while (child < size) {
        if (child + 1 < size && LOWER(child + 1, child)) {
            child++;
        }
        if (LOWER(i, child)) {
            break;
        }
        SWAP(i, child);
        i = child;
        child = CHILD(i);
    }
}

/* Main function */
int main() {
    char symbol;
    int n;
    size = 0;
    while (scanf(" %c", &symbol) != EOF && symbol == 'R') {
        assert(scanf("egister %d %d", &heap[size].key, &heap[size].period) 
                != EOF);
        heap[size].time = heap[size].period;
        move_up(size++);
    }
    assert(scanf("%d", &n) != EOF);
    for (; n > 0; n--) {
        printf("%d\n", heap[0].key);
        heap[0].time += heap[0].period;
        move_down();
    }
    return 0;
}
