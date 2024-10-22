/* 10010
 * Where's Waldorf?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION       50
#define MAX_STRING          (MAX_DIMENSION + 2)
#define NUM_DIRECTIONS      8

typedef char string_t[MAX_STRING];

string_t grid[MAX_DIMENSION];
int rows, columns;

int drow[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dcol[] = {0, 1, 1, 1, 0, -1, -1, -1};

/* Search for a word in the grid and print the first occurrence */
void search(string_t *word, int size) {
    int r, c, d, i, checks;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < columns; c++) {
            if (tolower(grid[r][c]) == tolower((*word)[0])) {
                for (d = 0; d < NUM_DIRECTIONS; d++) {
                    if ((drow[d] == -1 && r < size - 1) || 
                            (drow[d] == 1 && r > rows - size) ||
                            (dcol[d] == -1 && c < size - 1) ||
                            (dcol[d] == 1 && c > columns - size)) {
                        continue;
                    }
                    for (i = 1, checks = 1; checks && i < size; i++) {
                        checks = tolower(grid[r + drow[d] * i][c + dcol[d] * i]) == 
                                tolower((*word)[i]);
                    }
                    if (checks) {
                        printf("%d %d\n", r + 1, c + 1);
                        return;
                    }
                }
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_words;
        assert(scanf("%d %d", &rows, &columns) != EOF);
        for (i = 0; i < rows; i++) {
            assert(scanf(" %s", grid[i]) != EOF);
        }
        assert(scanf("%d", &num_words) != EOF);
        for (i = 0; i < num_words; i++) {
            string_t word;
            assert(scanf(" %s", word) != EOF);
            search(&word, strlen(word));
        }
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
