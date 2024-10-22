/* 10720
 * Graph Construction
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define PARENT(x)   (((x) - 1) / 2)
#define CHILD(x)    (2 * (x) + 1)
#define SWAP(x,y)   do { \
    int _s = heap[x]; heap[x] = heap[y]; heap[y] = _s; } while (0)

int heap[MAX_N], size;

/* Insert into heap */
void insert_heap(int value) {
    int index, parent;
    heap[size] = value;
    index = size++;
    while (index > 0) {
        parent = PARENT(index);
        if (heap[parent] > heap[index])
            break;
        SWAP(parent, index);
        index = parent;
    }
}

/* Remove maximal element */
int remove_heap() {
    int index, child, maximum = heap[0];
    heap[0] = heap[--size];
    index = 0;
    while ((child = CHILD(index)) < size) {
        if (child < size - 1 && heap[child + 1] > heap[child])
            child++;
        if (heap[child] < heap[index])
            break;
        SWAP(child, index);
        index = child;
    }
    return maximum;
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, j, value, degree, sum, possible;
        for (i = size = sum = 0; i < n; i++) {
            assert(scanf("%d", &value) == 1);
            if (value > 0)
                insert_heap(value);
            sum += value;
        }
        possible = sum % 2 == 0 && sum <= n * n - n;
        for (i = degree = 0; possible && size > 0 && i < n; i++) {
            possible = size >= degree;
            if (possible) {
                int stack[MAX_N];
                for (j = 0; j < degree; j++)
                    stack[j] = remove_heap();
                for (j = 0; j < degree; j++)
                    if (stack[j] > 1)
                        insert_heap(stack[j] - 1);
                degree = size > 0 ? remove_heap() : 0;
            }
        }
        possible &= size == 0 && degree == 0;
        printf("%sossible\n", possible ? "P" : "Not p");
    }
    return EXIT_SUCCESS;
}
