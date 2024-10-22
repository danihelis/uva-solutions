/* 422
 * Word-Search Wonder
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_STRING  (MAX_DIM + 10)
#define MAX_DIRECT  8

typedef char string_t[MAX_STRING];

string_t matrix[MAX_DIM];
int dim;

/* Search and print coordinates of a word */
void search(char *word) {
    static int drow[MAX_DIRECT] = {-1, -1, 0, 1, 1, 1, 0, -1};
    static int dcol[MAX_DIRECT] = {0, 1, 1, 1, 0, -1, -1, -1};
    int row, col, d, k, size, found;
    for (row = 0, size = strlen(word); row < dim; row++) {
        for (col = 0; col < dim; col++) {
            if (word[0] == matrix[row][col]) {
                for (d = 0; d < MAX_DIRECT; d++) {
                    if ((drow[d] == -1 && row < size - 1) || 
                            (drow[d] == 1 && row > dim - size) ||
                            (dcol[d] == -1 && col < size - 1) || 
                            (dcol[d] == 1 && col > dim - size)) {
                        continue;
                    }
                    for (k = 1, found = 1; found && k < size; k++) {
                        found = (word[k] == matrix[row + drow[d] * k][col + dcol[d] * k]);
                    }
                    if (found) {
                        printf("%d,%d %d,%d\n", row + 1, col + 1, row + drow[d] * (size - 1) + 1,
                                col + dcol[d] * (size - 1) + 1);
                        return;
                    }
                }
            }
        }
    }
    printf("Not found\n");
}

/* Main function */
int main() {
    string_t input;
    assert(scanf("%s", input) != EOF);
    while (sscanf(input, "%d", &dim) == 1 && dim > 0) {
        int i;
        for (i = 0; i < dim; i++) {
            assert(scanf(" %s", matrix[i]) != EOF);
        }
        while (scanf(" %s", input) != EOF && isalpha(input[0])) {
            search(input);
        }
    }
    return 0;
}
