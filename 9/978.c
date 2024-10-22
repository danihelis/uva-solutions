/* 978
 * Lemmings Battle!
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    100000

#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define PARENT(i)   (((i) - 1) / 2)
#define CHILD(i)    ((i) * 2 + 1)

#define SWAP(i,j)   do { \
        int swap = i; \
        i = j; \
        j = swap; \
    } while (0)

/* Insert into heap as last and move up */
void insert(int *heap, int *size, int value) {
    int i, parent;
    heap[(*size)++] = value;
    i = (*size) - 1;
    parent = PARENT(i);
    while (i > 0 && heap[i] > heap[parent]) {
        SWAP(heap[i], heap[parent]);
        i = parent;
        parent = PARENT(i);
    }
}

/* Remove top and move last item top and then down in heap */
int get_maximum(int *heap, int *size) {
    int i, child, maximum;
    maximum = heap[0];
    heap[0] = heap[--(*size)];
    i = 0;
    child = CHILD(i);
    while (child < *size) {
        if (child + 1 < *size && heap[child + 1] > heap[child]) {
            child++;
        }
        if (heap[child] <= heap[i]) {
            break;
        }
        SWAP(heap[child], heap[i]);
        i = child;
        child = CHILD(i);
    }
    return maximum;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int heap[2][MAX_SIZE], battle[2][MAX_SIZE], size[2], total[2], 
            num_battles, i, k, value, win;
        assert(scanf("%d %d %d", &num_battles, &total[0], &total[1]) != EOF);
        for (k = 0; k < 2; k++) {
            for (i = 0, size[k] = 0; i < total[k]; i++) {
                assert(scanf("%d", &value) != EOF);
                insert(heap[k], &size[k], value);
            }
        }
        while (size[0] > 0 && size[1] > 0) {
            num_battles = MIN(num_battles, MIN(size[0], size[1]));
            for (i = 0; i < num_battles; i++) {
                for (k = 0; k < 2; k++) {
                    battle[k][i] = get_maximum(heap[k], &size[k]);
                }
            }
            for (i = 0; i < num_battles; i++) {
                win = battle[0][i] > battle[1][i] ? 0 : 1;
                battle[win][i] -= battle[1 - win][i];
                if (battle[win][i] > 0) {
                    insert(heap[win], &size[win], battle[win][i]);
                }
            }
        }
        win = size[0] > 0 ? 0 : 1;
        if (size[win] == 0) {
            printf("green and blue died\n");
        }
        else {
            printf("%s wins\n", win == 0 ? "green" : "blue");
            while (size[win] > 0) {
                printf("%d\n", get_maximum(heap[win], &size[win]));
            }
        }
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
