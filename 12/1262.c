/* 1262
 * Password
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ROWS        6
#define COLS        5
#define MAX_STRING  (COLS + 2)

/* Compare two characters */
int compare(const void *a, const void * b) {
    return * (char *) a - * (char *) b;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        char matrix[2][ROWS][MAX_STRING], common[COLS][MAX_STRING];
        int i, j, k, found, num_commons[COLS], comb[COLS + 1], index;
        assert(scanf("%d", &index) == 1);
        for (k = 0; k < 2; k++)
            for (i = 0; i < ROWS; i++)
                assert(scanf(" %s", matrix[k][i]) == 1);
        for (i = 0; i < COLS; i++) {
            num_commons[i] = 0;
            memset(common[i], 0, MAX_STRING);
            for (k = 0; k < ROWS; k++) {
                char c = matrix[0][k][i];
                for (j = found = 0; !found && j < ROWS; j++)
                    found = matrix[1][j][i] == c;
                if (found && strchr(common[i], c) == NULL)
                    common[i][num_commons[i]++] = c;
            }
            qsort(common[i], num_commons[i], sizeof (char), compare);
        }
        comb[COLS] = 1;
        for (i = COLS - 1; i >= 0; i--)
            comb[i] = comb[i + 1] * num_commons[i];
        if (--index >= comb[0])
            printf("NO\n");
        else {
            for (i = 0; i < COLS; i++) {
                assert(index < comb[i]);
                printf("%c", common[i][index / comb[i + 1]]);
                index %= comb[i + 1];
            }
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
