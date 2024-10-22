/* 11995
 * I Can Guess the Data Structure!
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX     1001

#define SWAP(a, b)  do { \
        int swap = heap[a]; \
        heap[a] = heap[b]; \
        heap[b] = swap; \
    } while (0)

int stack[MAX], queue[MAX], heap[MAX];
int top, front, rear, size;
char stack_error, queue_error, heap_error;

/* Main function */
int main() {
    int i, n, solutions;
    while (scanf("%d", &n) != EOF) {
        top = front = rear = size = 0;
        stack_error = queue_error = heap_error = 0;
        for (i = 0; i < n; i++) {
            int op, value;
            assert(scanf("%d %d", &op, &value) != EOF);
            if (!stack_error) {
                if (op == 1) {
                    stack[top++] = value;
                }
                else {
                    stack_error = top == 0 || stack[--top] != value;
                }
            }
            if (!queue_error) {
                if (op == 1) {
                    queue[rear++] = value;
                }
                else {
                    queue_error = front >= rear || queue[front++] != value;
                }
            }
            if (!heap_error) {
                if (op == 1) {
                    int i = size, parent = (i - 1) / 2;
                    heap[size++] = value;
                    while (i > 0 && heap[parent] < heap[i]) {
                        SWAP(parent, i);
                        i = parent;
                        parent = (i - 1) / 2;
                    }
                }
                else {
                    heap_error = size == 0 || heap[0] != value;
                    if (!heap_error) {
                        int i = 0, child = 1;
                        heap[0] = heap[--size];
                        while (child < size) {
                            if (child + 1 < size && heap[child + 1] > 
                                    heap[child]) {
                                child++;
                            }
                            if (heap[child] < heap[i])
                                break;
                            SWAP(child, i);
                            i = child;
                            child = i * 2 + 1;
                        }
                    }
                }
            }
        }
        solutions = (stack_error ? 0 : 1) + (queue_error ? 0 : 1) +
                (heap_error ? 0 : 1);
        printf("%s\n", solutions == 0 ? "impossible" : 
                solutions > 1 ?"not sure" : !stack_error ? "stack" : 
                !queue_error ? "queue" : "priority queue");
    }
    return 0;
}
