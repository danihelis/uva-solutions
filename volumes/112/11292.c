/* 11292
 * Dragon of Loowater
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     20000

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Read vector and sort it */
void read_and_sort(int vector[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        assert(scanf("%d", &vector[i]) != EOF);
    }
    qsort(vector, size, sizeof (int), compare);
}

/* Main function */
int main() {
    int head[MAX_DIM], knight[MAX_DIM];
    int num_heads, num_knights;
    while (scanf("%d %d", &num_heads, &num_knights) != EOF && 
            !(num_heads == 0 && num_knights == 0)) {
        int h, k, cost;
        read_and_sort(head, num_heads);
        read_and_sort(knight, num_knights);
        for (h = 0, k = 0, cost = 0; 
                (num_heads - h) <= (num_knights - k) && h < num_heads && k < num_knights; k++) {
            if (knight[k] >= head[h]) {
                cost += knight[k];
                h++;
            }
        }
        if (h < num_heads) {
            printf("Loowater is doomed!\n");
        }
        else {
            printf("%d\n", cost);
        }
    }
    return 0;
}
