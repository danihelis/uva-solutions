/* 10954
 * Add All
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_HEAP    5000
#define PARENT(i)   (((i) - 1) / 2)
#define CHILD(i)    ((i) * 2 + 1)
#define SWAP(a,b)   do { \
        int swap = heap[a]; \
        heap[a] = heap[b]; \
        heap[b] = swap; \
    } while (0)

int heap[MAX_HEAP], size;

/* Insert into heap */
void insert(int value) {
    int i = size, parent = PARENT(size);
    heap[size++] = value;
    while (i > 0 && heap[parent] > heap[i]) {
        SWAP(parent, i);
        i = parent;
        parent = PARENT(i);
    }
}

/* Remove from heap */
int get_top() {
    int i = 0, child = CHILD(0), top = heap[0];
    heap[0] = heap[--size];
    while (child < size) {
        if (child + 1 < size && heap[child + 1] < heap[child]) {
            child++;
        }
        if (heap[child] >= heap[i]) {
            break;
        }
        SWAP(child, i);
        i = child;
        child = CHILD(i);
    }
    return top;
}

/* Main function */
int main() {
    int i, n, value, cost;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (i = 0, size = 0, cost = 0; i < n; i++) {
            assert(scanf("%d", &value) != EOF);
            insert(value);
        }
        while (size > 1) {
            int sum = get_top() + get_top(); 
            cost += sum;
            insert(sum);
        }
        printf("%d\n", cost);
    }
    return 0;
}
