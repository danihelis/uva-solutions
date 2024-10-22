/* 11507
 * Bender B. Rodriguez Problem
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_INPUT 5

typedef enum {
    X_PLUS = 0,
    X_MINUS,
    Y_PLUS,
    Y_MINUS,
    Z_PLUS,
    Z_MINUS
} dir_t;

dir_t y_cycle[] = {X_PLUS, Y_PLUS, X_MINUS, Y_MINUS};
dir_t z_cycle[] = {X_PLUS, Z_PLUS, X_MINUS, Z_MINUS};
int num_cycles = sizeof (y_cycle) / sizeof (dir_t);

/* Find position in cycle, if any */
int find_pos(dir_t val, dir_t cycle[]) {
    int i;
    for (i = 0; i < num_cycles; i++) {
        if (cycle[i] == val) {
            return i;
        }
    }
    return -1;
}

/* Main function */
int main() {
    int i, n, index;
    while (scanf("%d ", &n) != EOF && n > 0) {
        dir_t *cycle, dir = X_PLUS;
        for (i = 1; i < n; i++) {
            char input[MAX_INPUT];
            assert(scanf("%s ", input) != EOF);
            if (input[0] == 'N') {
                continue;
            }
            cycle = input[1] == 'z' ? z_cycle : y_cycle;
            index = find_pos(dir, cycle);
            if (index != -1) {
                index = (index + num_cycles + (input[0] == '+' ? 1 : -1)) % num_cycles;
                dir = cycle[index];
            }
        }
        printf("%c%c\n", dir % 2 == 0 ? '+' : '-', dir < 2 ? 'x' : dir < 4 ? 'y' : 'z');
    }
    return 0;
}
