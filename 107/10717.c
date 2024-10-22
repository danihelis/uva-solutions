/* 10717
 * Mint
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TYPES   50
#define NUM_LEGS    4

int type[MAX_TYPES];
int num_types;

/* Compare two integers in ascending order */
int comp_ascending(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compare two integers in descending order */
int comp_descending(const void *a, const void *b) {
    return *((int *) b) - *((int *) a);
}

/* Find best length for all legs, either above or below the limit */
int compute_length(int height, int above) {
    int length[MAX_TYPES], i;
    while (1) {
        for (i = 0; i < num_types; i++) {
            length[i] = (height / type[i])  * type[i];
            if (above && length[i] < height) {
                length[i] += type[i];
            }
        }
        qsort(length, num_types, sizeof (int), (above ? comp_ascending : comp_descending));
        if (length[NUM_LEGS - 1] == height) {
            return height;
        }
        height = length[NUM_LEGS - 1];
    }
    assert(NULL);
    return 0;
}

/* Main function */
int main() {
    int num_tables, height, i;
    while (scanf("%d %d", &num_types, &num_tables) != EOF && num_types > 0) {
        for (i = 0; i < num_types; i++) {
            assert(scanf("%d", &type[i]) != EOF);
        }
        for (i = 0; i < num_tables; i++) {
            assert(scanf("%d", &height) != EOF);
            printf("%d %d\n", compute_length(height, 0), compute_length(height, 1));
        }
    }
    return 0;
}
