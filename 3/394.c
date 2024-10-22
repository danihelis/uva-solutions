/* 394
 * Mapmaker
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME 15
#define MAX_ARRAYS 1000
#define MAX_DIMENSION 10

typedef struct {
    char name[MAX_NAME];
    int base;
    int size;
    int dimension;
    int lower[MAX_DIMENSION];
    int upper[MAX_DIMENSION];
    int coefficient[MAX_DIMENSION + 1];
} array_t;

array_t array[MAX_ARRAYS];
int num_arrays;

/* Read array definition and create new array */
void create_array() {
    array_t *current = &array[num_arrays];
    int d, sum = 0;
    assert(scanf(" %s %d %d %d", current->name, &current->base, &current->size, 
                &current->dimension) != EOF);
    for (d = 0; d < current->dimension; d++) {
        assert(scanf("%d %d", &current->lower[d], &current->upper[d]));
    }
    current->coefficient[current->dimension] = current->size;
    for (d = current->dimension - 1; d > 0; d--) {
        current->coefficient[d] = current->coefficient[d + 1] * (current->upper[d] - 
                current->lower[d] + 1);
        sum += current->coefficient[d] * current->lower[d - 1];
    }
    current->coefficient[0] = current->base - sum - current->size * 
            current->lower[current->dimension - 1];
    num_arrays++;
}

/* Search for an array */
array_t * search_array(char *name) {
    int i;
    for (i = 0; i < num_arrays; i++) {
        if (strcmp(name, array[i].name) == 0) {
            return &array[i];
        }
    }
    return NULL;
}

/* Read array position and calculate physical address */
void calculate_physical_address() {
    char name[MAX_NAME];
    int address, d;
    array_t *current;
    assert(scanf(" %s", name) != EOF);
    current = search_array(name);
    assert(current != NULL);
    printf("%s[", name);

    address = current->coefficient[0];
    for (d = 0; d < current->dimension; d++) {
        int pos;
        assert(scanf("%d", &pos) != EOF);
        printf("%s%d", (d > 0 ? ", " : ""), pos);
        address += current->coefficient[d + 1] * pos;
    }
    printf("] = %d\n", address);
}

/* Main function */
int main() {
    int i, definitions, positions;
    num_arrays = 0;
    assert(scanf("%d %d", &definitions, &positions) != EOF);
    for (i = 0; i < definitions; i++) {
        create_array();
    }
    for (i = 0; i < positions; i++) {
        calculate_physical_address();
    }
    return 0;
}
