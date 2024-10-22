/* 443
 * Humble Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAXIMUM     2000000000L
#define MAX_SIZE    6000
#define PARENT(i)   (((i) - 1) / 2)
#define CHILD(i)    (2 * (i) + 1)
#define SWAP(i, j)  do { \
        elem_t swap = heap[i]; \
        heap[i] = heap[j]; \
        heap[j] = swap; \
    } while (0)

typedef struct {
    long value;
    int multiple;
} elem_t;

elem_t heap[MAX_SIZE];
long humble[MAX_SIZE];
int size_heap, num_humbles;

/* Insert value into heap */
void insert_heap(long value, int multiple) {
    int parent, index = size_heap++;
    heap[index].value = value, heap[index].multiple = multiple;
    while (index > 0 && 
            heap[parent = PARENT(index)].value > heap[index].value) {
        SWAP(index, parent);
        index = parent;
    }
}

/* Remove minimum value from heap */
elem_t remove_heap() {
    int index, child;
    elem_t minimum = heap[0];
    if (--size_heap > 0) {
        SWAP(0, size_heap);
        index = 0;
        while ((child = CHILD(index)) < size_heap) {
            if (child + 1 < size_heap && 
                    heap[child + 1].value < heap[child].value)
                child++;
            if (heap[child].value < heap[index].value) {
                SWAP(index, child);
                index = child;
            }
            else
                break;
        }
    }
    return minimum;
}

/* Fill humble numbers up to index-th and return last */
int get_humble(int index) {
    while (num_humbles < index) {
        int i;
        elem_t minimum = remove_heap();
        for (i = minimum.multiple; i <= 7; i += (i == 2 ? 1 : 2)) {
            long value = minimum.value * i;
            if (value <= MAXIMUM)
                insert_heap(value, i);
        }
        humble[num_humbles++] = minimum.value;
    }
    return humble[index - 1];
}

/* Main function */
int main() {
    int index;
    heap[0].value = 1, heap[0].multiple = 2;
    size_heap = 1, num_humbles = 0;
    while (scanf("%d", &index) != EOF && index > 0) {
        int suffix = (index % 10) + ((index / 10) % 10 == 1 ? 10 : 0);
        printf("The %d%s humble number is %d.\n", index,
                suffix == 1 ? "st" : suffix == 2 ? "nd" :
                suffix == 3 ? "rd" : "th", get_humble(index));
    }
    return EXIT_SUCCESS;
}
