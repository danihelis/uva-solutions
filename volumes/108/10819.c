/* 10819
 * Trouble of 13-Dots
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BONUS           200
#define THRESHOLD       2000
#define MAX_N           100
#define MAX_VALUE       5
#define MAX_TOTAL_VALUE (MAX_VALUE * MAX_N)

typedef struct {
    int cost, value, threshold;
} item_t;

item_t item[MAX_N], bag[MAX_TOTAL_VALUE];
int num_items, bag_size, budget;

/* Insert or update value */
void insert_update(int value, int cost) {
    int start = 0, end = bag_size;
    while (start < end) {
        int middle = (start + end) / 2;
        if (bag[middle].value == value) {
            if (bag[middle].cost > cost)
                bag[middle].cost = cost;
            return;
        }
        else if (bag[middle].value < value)
            start = middle + 1;
        else
            end = middle;
    }
    for (end = bag_size; end > start; end--)
        bag[end] = bag[end - 1];
    bag[start].value = value, bag[start].cost = cost;
    bag[start].threshold = cost > THRESHOLD;
    bag_size++;
}

/* Find best value for the budget */
int find_best_selection() {
    int i, j;
    bag[0].cost = 0, bag[0].value = 0, bag[0].threshold = 0;
    bag_size = 1;
    for (i = 0; i < num_items; i++)
        for (j = bag_size - 1; j >= 0; j--) {
            int new_value = item[i].value + bag[j].value;
            int new_cost = item[i].cost + bag[j].cost;
            if (new_cost <= budget + BONUS)
                insert_update(new_value, new_cost);
        }
    for (j = bag_size - 1; j > 0; j--)
        if (bag[j].cost <= budget || bag[j].threshold)
            return bag[j].value;
    return 0;
}

/* Main function */
int main() {
    while (scanf("%d %d", &budget, &num_items) != EOF) {
        int i;
        for (i = 0; i < num_items; i++)
            assert(scanf("%d %d", &item[i].cost, &item[i].value) != EOF);
        printf("%d\n", find_best_selection());
    }
    return EXIT_SUCCESS;
}
