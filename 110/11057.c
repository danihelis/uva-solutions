/* 11057
 * Exact Sum
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

int vector[MAX_N], n;

/* Compare */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Binary search */
int find(int value) {
    int start = 0, end = n;
    while (start < end) {
        int middle = (start + end) / 2;
        if (vector[middle] == value)
            return middle;
        else if (vector[middle] < value)
            start = middle + 1;
        else
            end = middle;
    }
    return start;
}

/* Main function */
int main() {
    while (scanf("%d", &n) != EOF) {
        int i, *pos, sum, middle;
        for (i = 0; i < n; i++)
            assert(scanf("%d", &vector[i]) != EOF);
        assert(scanf("%d", &sum) != EOF);
        qsort(vector, n, sizeof (int), compare);
        middle = find(sum / 2);
        for (i = middle, pos = NULL; pos == NULL && i < n; i++) {
            int key = sum - vector[i];
            pos = bsearch(&key, vector, n, sizeof (int), compare);
        }
        assert(pos != NULL);
        printf("Peter should buy books whose prices are %d and %d.\n\n",
                *pos, vector[--i]);
    }
    return EXIT_SUCCESS;
}
