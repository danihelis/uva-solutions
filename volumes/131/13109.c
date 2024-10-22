/* 13109
 * Elephants
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_M 100000
#define PARENT(i)   ((i - 1) / 2)
#define CHILD(i)    (2 * i + 1)

#define SWAP(h, a, b)  do { \
    int swap = h[a]; h[a] = h[b]; h[b] = swap; \
    a = b; \
} while(0)

int heap[MAX_M], size, sum;

/* Insert into heap */
void insert_heap(int value) {
    int index = size++;
    heap[index] = value;
    while (index > 0 && heap[PARENT(index)] < heap[index]) {
        SWAP(heap, index, PARENT(index));
    }
    sum += value;
}

/* Remove top element */
void remove_heap() {
    int index = 0, child;
    sum -= heap[0];
    heap[index] = heap[--size];
    while ((child = CHILD(index)) < size) {
        if (child + 1 < size && heap[child + 1] > heap[child]) child++;
        if (heap[index] > heap[child]) break;
        SWAP(heap, index, child);
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int m, limit, weight;
        assert(scanf("%d %d", &m, &limit) != EOF);
        for (size = 0, sum = 0; m > 0; m--) {
            assert(scanf("%d", &weight) != EOF);
            if (weight + sum <= limit) {
                insert_heap(weight);
            } else if (size > 0 && weight < heap[0]) {
                remove_heap();
                insert_heap(weight);
            }
        }
        printf("%d\n", size);
    }
    return EXIT_SUCCESS;
}
