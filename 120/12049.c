/* 12049
 * Just Prune The List
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000

typedef struct {
    unsigned int value, count;
} entry_t;

entry_t list[2][MAX_N];
int size[2];

/* Increment count */
void increment(unsigned int value, entry_t *list, int *size) {
    int start = 0, end = *size;
    while (start < end) {
        int mid = (start + end) / 2;
        if (list[mid].value == value) {
            list[mid].count++;
            return;
        }
        else if (list[mid].value > value)
            end = mid;
        else
            start = mid + 1;
    }
    for (end = (*size)++; end > start; end--)
        list[end] = list[end - 1];
    list[start].value = value, list[start].count = 1;
}

/* Return the number of different elements from lists */
#define INSIZE(k)   (i[k] < size[k])
#define VALUE(k)    (list[k][i[k]].value)
#define COUNT(k)    (list[k][i[k]++].count)
int difference() {
    int k, i[2], count;
    count = i[0] = i[1] = 0;
    while (INSIZE(0) && INSIZE(1)) {
        if (VALUE(0) == VALUE(1))
            count += abs(COUNT(0) - COUNT(1));
        else if (VALUE(0) < VALUE(1))
            count += COUNT(0);
        else
            count += COUNT(1);
    }
    for (k = 0; k < 2; k++)
        while (INSIZE(k))
            count += COUNT(k);
    return count;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        unsigned int i, k, value, n[2];
        assert(scanf("%u %u", &n[0], &n[1]) == 2);
        for (k = 0; k < 2; k++) {
            for (i = size[k] = 0; i < n[k]; i++) {
                assert(scanf("%u", &value) == 1);
                increment(value, list[k], &size[k]);
            }
        }
        printf("%d\n", difference());
    }
    return EXIT_SUCCESS;
}
