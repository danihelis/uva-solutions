/* 11100
 * The Trip, 2007
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ITEMS   10000

typedef struct {
    int size, index;
} item_t;

item_t item[MAX_ITEMS];
int num_items;

/* Compare sizes */
int compare_sizes(const void *a, const void *b) {
    return ((item_t *) a)->size - ((item_t *) b)->size;
}

/* Compare indexes */
int compare_index(const void *a, const void *b) {
    return ((item_t *) a)->index - ((item_t *) b)->index;
}

/* Organize bags */
void organize_bags() {
    int i, last, repeat, num_bags;
    qsort(item, num_items, sizeof (item_t), compare_sizes);
    for (i = num_bags = repeat = 0, last = -1; i < num_items; i++) {
        if (item[i].size != last) {
            if (repeat > num_bags)
                num_bags = repeat;
            repeat = 0;
        }
        repeat++;
        last = item[i].size;
    }
    num_bags = repeat > num_bags ? repeat : num_bags;
    for (i = 0; i < num_items; i++)
        item[i].index = i % num_bags;
    qsort(item, num_items, sizeof (item_t), compare_index);
    printf("%d", num_bags);
    for (i = 0, last = -1; i < num_items; i++) {
        printf("%s%d", item[i].index != last ? "\n" : " ", item[i].size);
        last = item[i].index;
    }
    printf("\n");
}

/* Main function */
int main() {
    int i, first = 1;
    while (scanf("%d", &num_items) != EOF && num_items > 0) {
        (first ? (first = 0) : printf("\n"));
        for (i = 0; i < num_items; i++)
            assert(scanf("%d", &item[i].size) != EOF);
        organize_bags();
    }
    return EXIT_SUCCESS;
}
