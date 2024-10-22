/* 13190
 * Rockabye Tobby
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           3000
#define MAX_STRING      16

#define PARENT(i)       (((i) - 1) / 2)
#define CHILD(i)        ((i) * 2 + 1)
#define SMALLER(a,b)    (heap[a]->time == heap[b]->time ? \
                             heap[a]->index < heap[b]->index : \
                             heap[a]->time < heap[b]->time)
#define SWAP(a,b)       do { \
    entry_t *_swap = heap[a]; \
    heap[a] = heap[b]; \
    heap[b] = _swap; \
    a = b; \
} while (0)


typedef struct {
    char name[MAX_STRING];
    int frequency, index, time;
} entry_t;

int heap_size;
entry_t data[MAX_N], *heap[MAX_N];

/* Insert into heap */
void insert_heap(entry_t *e) {
    int index = heap_size;
    heap[heap_size++] = e;
    while (index > 0 && SMALLER(index, PARENT(index))) {
        SWAP(index, PARENT(index));
    }
}

/* Remove from heap */
entry_t * remove_heap() {
    entry_t *removed = heap[0];
    int index = 0, child;
    heap[0] = heap[--heap_size];
    while ((child = CHILD(index)) < heap_size) {
        if (child + 1 < heap_size && SMALLER(child + 1, child)) child++;
        if (SMALLER(child, index)) SWAP(index, child);
        else break;
    }
    return removed;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int i, n, k;
        assert(scanf("%d %d", &n, &k) == 2);
        for (i = heap_size = 0; i < n; i++) {
            entry_t *e = &data[i];
            assert(scanf(" %s %d", e->name, &e->frequency) == 2);
            e->time = e->frequency, e->index = i;
            insert_heap(e);
        }
        while (k-- > 0) {
            entry_t *e = remove_heap();
            printf("%d %s\n", e->time, e->name);
            e->time += e->frequency;
            insert_heap(e);
        }
    }
    return EXIT_SUCCESS;
}
