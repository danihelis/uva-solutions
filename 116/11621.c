/* 11621
 * Small Factors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX_VALUE   (1L << 31)

long list[MAX_N];
int size;

/* Compare two long integers */
int compare(const void *a, const void *b) {
    return *((long *) a) < *((long *) b) ? -1 : 1;
}

/* Create list of numbers */
void create_list() {
    int i, end;
    long value, factor;
    for (size = 0, value = 1; value <= MAX_VALUE; value *= 2) {
        list[size++] = value;
    }
    end = size;
    for (factor = 3; factor < MAX_VALUE; factor *= 3) {
        for (i = 0; i < end; i++) {
            long multiple = list[i] * factor;
            if (multiple > MAX_VALUE) break;
            list[size++] = multiple;
        }
    }
    qsort(list, size, sizeof (long), compare);
}

/* Binary search for minimal number greater than or equal to value */
long find_minimal(long value) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        if (value == list[middle]) return value;
        if (value < list[middle]) end = middle;
        else start = middle + 1;
    }
    return list[start];
}

/* Main function */
int main() {
    long value;
    create_list();
    while (scanf("%ld", &value) != EOF && value > 0) {
        printf("%ld\n", find_minimal(value));
    }
    return EXIT_SUCCESS;
}
