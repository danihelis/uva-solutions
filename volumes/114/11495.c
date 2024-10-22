/* 11495
 * Bubbles and Buckets
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH 500000

int merge[MAX_LENGTH];

/* Calculate the number of swaps to sort the vector while merge-sort it */
long merge_swap(int vector[], int start, int end) {
    long swaps;
    int middle, first, second, index;
    if (end - start <= 1) {
        return 0;
    }
    middle = (start + end) / 2;
    swaps = merge_swap(vector, start, middle) + merge_swap(vector, middle, end);
    first = start;
    second = middle;
    index = 0;
    while (first < middle && second < end) {
        if (vector[first] <= vector[second]) {
            merge[index++] = vector[first++];
        }
        else {
            merge[index++] = vector[second++];
            swaps += middle - first;
        }
    }
    while (first < middle) {
        merge[index++] = vector[first++];
    }
    while (second < end) {
        merge[index++] = vector[second++];
    }
    for (index = 0; start < end; start++, index++) {
        vector[start] = merge[index];
    }
    return swaps;
}

/* Main function */
int main() {
    int vector[MAX_LENGTH];
    int i, size;
    while (scanf("%d", &size) != EOF) {
        long swaps;
        if (size == 0) {
            break;
        }
        for (i = 0; i < size; i++) {
            assert(scanf("%d", &vector[i]) != EOF);
        }
        swaps = merge_swap(vector, 0, size);
        printf("%s\n", (swaps % 2 == 0 ? "Carlos" : "Marcelo"));
    }
    return 0;
}
