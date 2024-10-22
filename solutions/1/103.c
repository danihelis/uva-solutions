/* 103
 * Stacking Boxes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BOXES 30
#define MAX_DIMENSIONS 10

typedef int dimension_t[MAX_DIMENSIONS];

typedef struct box_s {
    dimension_t dimension;
    struct box_s *over;
    int index, length;
} box_t, *box_p;

box_t box[MAX_BOXES];
box_p sequence[MAX_BOXES];
int num_boxes, num_dimensions;

/* Compare two integers in order to sort them */
int compare_integer(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compare two box pointers in order to sort them */
int compare_boxes(const void *a, const void *b) {
    return (*((box_p *) a))->dimension[0] - (*((box_p *) b))->dimension[0];
}

/* Whether a larger box can contain a smaller box */
int can_contain(box_p larger, box_p smaller) {
    int i;
    for (i = 0; i < num_dimensions; i++) {
        if (larger->dimension[i] <= smaller->dimension[i]) {
            return 0;
        }
    }
    return 1;
}

/* Find best sequence of boxes and output it */
void find_best_sequence() {
    box_p solution[MAX_BOXES];
    box_p best;
    int i, j, length;
    qsort(sequence, num_boxes, sizeof (box_p), compare_boxes);
    for (i = 1, best = sequence[0]; i < num_boxes; i++) {
        box_p larger = sequence[i];
        for (j = i - 1; j >= 0; j--) {
            box_p smaller = sequence[j];
            if (smaller->length >= larger->length && can_contain(larger, smaller)) {
                larger->over = smaller;
                larger->length = smaller->length + 1;
                if (larger->length > best->length) {
                    best = larger;
                }
            }
        }
    }
    for (i = best->length, length = best->length + 1; i >= 0; i--, best = best->over) {
        assert(best != NULL);
        solution[i] = best;
    }
    assert(best == NULL);
    printf("%d\n", length);
    for (i = 0; i < length; i++) {
        printf("%d%c", solution[i]->index, (i < length - 1 ? ' ' : '\n'));
    }
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_boxes, &num_dimensions) != EOF) {
        int i, j;
        for (i = 0; i < num_boxes; i++) {
            box[i].index = i + 1;
            box[i].over = NULL;
            box[i].length = 0;
            sequence[i] = &box[i];
            for (j = 0; j < num_dimensions; j++) {
                assert(scanf("%d", &box[i].dimension[j]) != EOF);
            }
            qsort(box[i].dimension, num_dimensions, sizeof (int), compare_integer);
        }
        find_best_sequence();
    }
    return 0;
}
