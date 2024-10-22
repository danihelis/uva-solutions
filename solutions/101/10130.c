/* 10130
 * SuperSale
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_OBJECTS 1000
#define MAX_WEIGHT 40
#define MAX_PEOPLE 100

typedef struct {
    int price, weight;
} object_t, *object_p;

object_t object[MAX_OBJECTS];
int num_objects;
int weight[MAX_WEIGHT];

/* Calculate the best price for up to a maximum weight */
void calculate_best_weight(int maximum) {
    int i, w, table[MAX_WEIGHT];
    memset(weight, 0, (maximum + 1) * sizeof (int));
    for (i = 0; i < num_objects; i++) {
        memcpy(table, weight, (maximum + 1) * sizeof (int));
        for (w = object[i].weight; w <= maximum; w++) {
            int diff = w - object[i].weight;
            if (object[i].price + table[diff] > weight[w]) {
                weight[w] = object[i].price + table[diff];
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int people[MAX_PEOPLE];
        int i, num_people, max_weight, sum;
        assert(scanf("%d", &num_objects) != EOF);
        for (i = 0; i < num_objects; i++) {
            assert(scanf("%d %d", &object[i].price, &object[i].weight) != EOF);
        }
        assert(scanf("%d", &num_people) != EOF);
        for (i = 0, max_weight = 0; i < num_people; i++) {
            assert(scanf("%d", &people[i]) != EOF);
            if (people[i] > max_weight) {
                max_weight = people[i];
            }
        }
        calculate_best_weight(max_weight);
        for (i = 0, sum = 0; i < num_people; i++) {
            sum += weight[people[i]];
        }
        printf("%d\n", sum);
    }
    return 0;
}
