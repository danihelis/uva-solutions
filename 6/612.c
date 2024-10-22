/* 612
 * DNA Sorting
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH 60
#define MAX_DIMENSION 100

typedef struct {
    char string[MAX_LENGTH];
    int distance, index;
} data_t, *data_p;

data_t data[MAX_DIMENSION];
data_p order[MAX_DIMENSION];

/* Calculate the unsortedness of a given string */
int unsortedness(char string[]) {
    char *pos, *ver;
    int distance = 0;
    for (pos = string; *pos != 0; pos++) {
        for (ver = pos + 1; *ver != 0; ver++) {
            if (*ver < *pos) {
                distance++;
            }
        }
    }
    return distance;
}

/* Compare two pointers to data_t in order to sort them */
int compare(const void *a, const void *b) {
    data_p x = *((data_p *) a), y = *((data_p *) b);
    return (x->distance == y->distance ? x->index - y->index : x->distance - y->distance);
}

/* Main function */
int main() {
    int num_tests, first_test;
    assert(scanf("%d", &num_tests) != EOF);
    for (first_test = 1; num_tests > 0; num_tests--) {
        int i, data_size;
        (first_test ? first_test = 0 : printf("\n"));
        assert(scanf(" %*d %d", &data_size) != EOF);
        for (i = 0; i < data_size; i++) {
            assert(scanf(" %[^\n]", data[i].string) != EOF);
            data[i].index = i;
            data[i].distance = unsortedness(data[i].string);
            order[i] = &data[i];
        }
        qsort(order, data_size, sizeof (data_p), compare);
        for (i = 0; i < data_size; i++) {
            printf("%s\n", order[i]->string);
        }
    }
    return 0;
}
