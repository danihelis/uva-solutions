/* 120
 * Stacks of Flapjacks
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ITEMS   50
#define MAX_STRING  (MAX_ITEMS * 5)

int stack[MAX_ITEMS], sorted[MAX_ITEMS], size;

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Flip the stack at some point */
void flip(int point) {
    int i, j;
    for (i = 0, j = point; i < j; i++, j--) {
        int swap = stack[i];
        stack[i] = stack[j];
        stack[j] = swap;
    }
    printf("%d ", size - point);
}

/* Sort the stack */
void sort() {
    int i, k;
    memcpy(sorted, stack, size * sizeof (int));
    qsort(sorted, size, sizeof (int), compare);
    for (i = size - 1; i > 0; i--) {
        if (stack[i] != sorted[i]) {
            for (k = 0; stack[k] != sorted[i]; k++)
                ;
            if (k > 0) {
                flip(k);
            }
            flip(i);
        }
    }
    printf("0\n");
}

/* Main function */
int main() {
    char line[MAX_STRING], *p;
    while (fgets(line, MAX_STRING, stdin) != NULL) {
        printf("%s", line);
        for (p = strtok(line, " "), size = 0; p != NULL; p = strtok(NULL, " "), size++) {
            stack[size] = atoi(p);
        }
        sort();
    }
    return 0;
}
