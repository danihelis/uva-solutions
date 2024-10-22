/* 11136
 * Hoax or what
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_LAYERS 20

typedef enum {
    MINIMUM,
    MAXIMUM
} type_t;

typedef struct {
    int *data;
    int size;
} layer_t;

layer_t layer[NUM_LAYERS + 1];

/* Create layers of sets */
void create_layers() {
    int i;
    for (i = 0; i <= NUM_LAYERS; i++) {
        layer[i].size = 1 << i;
        layer[i].data = (int *) malloc(layer[i].size * sizeof (int));
    }
}

/* Initialize layer */
void initialize_layers() {
    int i;
    for (i = 0; i <= NUM_LAYERS; i++) {
        memset(layer[i].data, 0, layer[i].size * sizeof (int));
    }
}

/* Add a new value to the structure */
void add(int value, int quantity) {
    int i;
    for (i = NUM_LAYERS; i >= 0; i--) {
        assert(value < layer[i].size);
        layer[i].data[value] += quantity;
        value >>= 1;
    }
}

/* Return either the minimum or maximum, and remove it from the structure */
int retrieve(type_t type) {
    int i, index, value;
    for (i = 0, index = 0; i < NUM_LAYERS; i++) {
        if (type == MINIMUM) {
            for (; layer[i].data[index] == 0 && index < layer[i].size; index++)
                ;
            assert(index < layer[i].size);
            index <<= 1;
        }
        else {
            for (; layer[i].data[index] == 0 && index >= 0; index--)
                ;
            assert(index >= 0);
            index = ((index + 1) << 1) - 1;
        }
    }
    value = (type == MINIMUM ? (layer[NUM_LAYERS].data[index] > 0 ? index : index + 1) :
            (layer[NUM_LAYERS].data[index] > 0 ? index : index - 1));
    add(value, -1);
    return value;
}

/* Main function */
int main() {
    int days;
    create_layers();
    while (scanf("%d", &days) != EOF && days != 0) {
        int i;
        long cost = 0;
        initialize_layers();
        for (i = 0; i < days; i++) {
            int j, bills;
            assert(scanf("%d", &bills) != EOF);
            for (j = 0; j < bills; j++) {
                int value;
                assert(scanf("%d", &value) != EOF);
                add(value, 1);
            }
            cost += retrieve(MAXIMUM) - retrieve(MINIMUM);
        }
        printf("%ld\n", cost);
    }
    return 0;
}
