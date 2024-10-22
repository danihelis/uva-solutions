/* 10192
 * Vacation
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CITIES  100
#define MAX_STRING  (MAX_CITIES + 2)

#define MAX(x, y)   ((x) > (y) ? (x) : (y))

/* Computes the longest common sequence */
int lcs(char *a, char *b) {
    int table[MAX_STRING][MAX_STRING];
    int i, j;
    char *ca, *cb;
    memset(table, 0, MAX_STRING * sizeof (int));
    for (i = 1, j = 0, ca = a; *ca != '\n'; i++, ca++) {
        table[i][0] = 0;
        for (j = 1, cb = b; *cb != '\n'; cb++, j++) {
            table[i][j] = MAX(table[i - 1][j], table[i][j - 1]);
            if (*ca == *cb) {
                table[i][j] = MAX(table[i - 1][j - 1] + 1, table[i][j]);
            }
        }
    }
    return table[i - 1][j - 1];
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int test = 0;
    char string[2][MAX_STRING];
    while (READ(string[0]) && READ(string[1]) && string[0][0] != '#') {
        printf("Case #%d: you can visit at most %d cities.\n", ++test, lcs(string[0], string[1]));
    }
    return 0;
}
