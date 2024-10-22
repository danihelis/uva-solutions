/* 910
 * TV game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CELLS   26
#define MAX_STEPS   31
#define NUM_NEXT    2

typedef struct {
    int next[NUM_NEXT];
    char special;
} cell_t;

cell_t cell[MAX_CELLS];
int solution[MAX_CELLS][MAX_STEPS];
int num_cells, num_steps;

/* Determine the number of choices that lead to the special cell */
int max_num_choices() {
    int s, c, k;
    for (c = 0; c < num_cells; c++) {
        solution[c][0] = (cell[c].special ? 1 : 0);
    }
    for (s = 1; s <= num_steps; s++) {
        for (c = 0; c < num_cells; c++) {
            solution[c][s] = 0;
            for (k = 0; k < NUM_NEXT; k++) {
                solution[c][s] += solution[cell[c].next[k]][s - 1];
            }
        }
    }
    return solution[0][num_steps];
}

/* Main function */
#define SET_NEXT(i, k, n) cell[(i) - 'A'].next[k] = ((n) - 'A')
int main() {
    while (scanf("%d", &num_cells) != EOF) {
        int i;
        for (i = 0; i < num_cells; i++) {
            char label, next[NUM_NEXT], special;
            assert(scanf(" %c %c %c %c", &label, &next[0], &next[1], &special) != EOF);
            SET_NEXT(label, 0, next[0]), SET_NEXT(label, 1, next[1]);
            cell[label - 'A'].special = (special == 'x');
        }
        assert(scanf("%d", &num_steps) != EOF);
        printf("%d\n", max_num_choices());
    }
    return 0;
}
