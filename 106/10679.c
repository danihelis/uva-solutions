/* 10679
 * I Love Strings!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100010
#define MAX_QUERY   1010

typedef struct {
    int index;
    long rank, order;
} suffix_t;

char string[MAX_STRING];
suffix_t suffix[MAX_STRING], *array[MAX_STRING];
int size;

/* Compare order */
int compare(const void *a, const void *b) {
    long diff = (* (suffix_t **) a)->order - (* (suffix_t **) b)->order;
    return diff < 0 ? -1 : diff > 0 ? 1 : 0;
}

/* Create suffix array */
void create_suffix_array() {
    int i, k;
    for (i = 0, size = strlen(string); i < size; i++) {
        suffix_t *s = &suffix[i];
        s->index = i, s->order = string[i];
        array[i] = s;
    }
    qsort(array, size, sizeof (suffix_t *), compare);
    for (k = 1; k < size; k *= 2) {
        for (array[0]->rank = 0, i = 1; i < size; i++)
            array[i]->rank = array[i - 1]->rank + 
                (array[i]->order > array[i - 1]->order ? 1 : 0);
        if (array[size - 1]->rank == size - 1)
            break;
        for (i = 0; i < size; i++)
            suffix[i].order = suffix[i].rank * size +
                (i + k < size ? suffix[i + k].rank : 0);
        qsort(array, size, sizeof (suffix_t *), compare);
    }
}

/* Find query with binary search */
int find_match(char *query) {
    int len = strlen(query);
    int start = 0, end = size;
    while (start < end) {
        int mid = (start + end) / 2;
        int cmp = strncmp(query, string + array[mid]->index, len);
        if (cmp == 0)
            return 1;
        else if (cmp < 0)
            end = mid;
        else
            start = mid + 1;
    }
    return 0;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int num_queries;
        assert(scanf(" %s %d", string, &num_queries) == 2);
        create_suffix_array();
        for (; num_queries > 0; num_queries--) {
            char query[MAX_QUERY];
            assert(scanf(" %s", query) == 1);
            printf("%c\n", find_match(query) ? 'y' : 'n');
        }
    }
    return EXIT_SUCCESS;
}

