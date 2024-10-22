/* 11003
 * Boxes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BOXES 1000
#define INFINITE 100000

#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int num_boxes;
    while (scanf("%d", &num_boxes) != EOF && num_boxes > 0) {
        int box_capacity[MAX_BOXES + 1];
        int i, length;
        box_capacity[0] = INFINITE, length = 1;
        for (i = 0; i < num_boxes; i++) {
            int weight, capacity, j;
            assert(scanf("%d %d", &weight, &capacity) != EOF);
            for (j = length; j > 0; j--) {
                int minimum = MIN(box_capacity[j - 1] - weight, capacity);
                if ((j == length && minimum >= 0) || minimum > box_capacity[j]) {
                    box_capacity[j] = minimum;
                    if (j == length) {
                        length++;
                    }
                }
            }
        }
        printf("%d\n", length - 1);
    }
    return 0;
}
