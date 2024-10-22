/* 10003
 * Cutting Sticks
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_POSITIONS 1010

int table[MAX_POSITIONS][MAX_POSITIONS];
int position[MAX_POSITIONS];
int num_positions;

/* Calculate the minimum cost of cutting all positions */
int calculate_minimum_cost() {
    int i, j, k;
    for (i = 0; i <= num_positions; i++) {
        table[i][i] = 0;
    }
    for (i = 1; i <= num_positions; i++) {
        for (j = i; j <= num_positions; j++) {
            int shift, minimum = -1;
            shift = j - i;
            for (k = 0; k < i; k++) {
                int size = table[shift][shift + k] + table[shift + k + 1][j];
                if (k == 0 || size < minimum) {
                    minimum = size;
                }
            }
            table[shift][j] = minimum + position[j] - (shift == 0 ? 0 : position[shift - 1]);
        }
    }
    return table[0][num_positions];
}

/* Main function */
int main() {
    int size;
    while (scanf("%d", &size) != EOF && size > 0) {
        int i;
        assert(scanf("%d", &num_positions) != EOF);
        for (i = 0; i < num_positions; i++) {
            assert(scanf("%d", &position[i]) != EOF);
        }
        position[i] = size;
        printf("The minimum cutting is %d.\n", calculate_minimum_cost());
    }
    return 0;
}
