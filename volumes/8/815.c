/* 815
 * Flooded!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define PARENT(i)   (((i) - 1) / 2)
#define CHILD(i)    (2 * (i) + 1)
#define SWAP(x, y)  do { \
        int _s = heap[x]; heap[x] = heap[y]; heap[y] = _s; \
    } while (0)

int heap[MAX_N], size;

/* Insert into heap */
void insert_heap(int value) {
    int index, parent;
    heap[size] = value;
    index = size++;
    while (index > 0) {
        parent = PARENT(index);
        if (heap[parent] > heap[index])
            SWAP(parent, index);
        else
            break;
        index = parent;
    }
}

/* Remove from heap */
int remove_heap() {
    int index, child, minimum;
    minimum = heap[0];
    heap[0] = heap[--size];
    index = 0;
    while ((child = CHILD(index)) < size) {
        if (child + 1 < size && heap[child + 1] < heap[child])
            child++;
        if (heap[child] < heap[index])
            SWAP(child, index);
        else
            break;
        index = child;
    }
    return minimum;
}

/* Main function */
int main() {
    int n, m, region = 0;
    while (scanf("%d %d", &n, &m) == 2 && n > 0) {
        int i, v, total, water, level, sum;
        double area, height;
        for (i = size = 0, total = n * m; i < total; i++) {
            assert(scanf("%d", &v) == 1);
            insert_heap(v);
        }
        assert(scanf("%d", &water) == 1);
        for (i = level = sum = 0; i < total - 1; i++) {
            int next, inc;
            level = remove_heap();
            next = heap[0];
            inc = (i + 1) * (next - level) * 100;
            if (sum + inc >= water)
                break;
            sum += inc;
        }
        if (i == total - 1)
            level = remove_heap();
        height = level + (water - sum) / (i + 1.0) / 100.0;
        area = (i + 1.0) / total * 100.0;
        printf("Region %d\n", ++region);
        printf("Water level is %.2f meters.\n", height);
        printf("%.2f percent of the region is under water.\n\n", area);
    }
    return EXIT_SUCCESS;
}
