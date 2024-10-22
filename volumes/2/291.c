/* 291
 * The House of Santa Claus
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_VERTICES 5
#define SEQ_LENGTH 8

#define MATRIX(x, y) matrix[(x < y ? x : y)][(x > y ? x : y)]

char matrix[NUM_VERTICES][NUM_VERTICES] = {{0, 1, 1, 0, 1}, {1, 0, 1, 0, 1}, {1, 1, 0, 1, 1}, 
    {0, 0, 1, 0, 1}, {1, 1, 1, 1, 0}};
char sequence[SEQ_LENGTH + 2];

/* Visit all possible edges */
void visit(int vertex, int index) {
    sequence[index] = vertex + '1';
    if (index >= SEQ_LENGTH) {
        printf("%s\n", sequence);
    }
    else {
        int i;
        for (i = 0; i < NUM_VERTICES; i++) {
            if (MATRIX(vertex, i)) {
                MATRIX(vertex, i) = 0;
                visit(i, index + 1);
                MATRIX(vertex, i) = 1;
            }
        }
    }
}

/* Main function */
int main() {
    memset(sequence, 0, SEQ_LENGTH + 2);
    visit(0, 0);
    return 0;
}
