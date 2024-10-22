/* 10066
 * The Twin Towers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    100
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

int sequence[2][MAX_SIZE];
int size[2];

/* Dynamic programming: largest common subsequence */
int lcs() {
    int table[MAX_SIZE + 1], previous[MAX_SIZE + 1];
    int i, j;
    memset(table, 0, (size[0] + 1) * sizeof (int));
    for (i = 0; i < size[1]; i++) {
        memcpy(previous, table, (size[0] + 1) * sizeof (int));
        for (j = 0; j < size[0]; j++) {
            table[j + 1] = MAX(table[j], previous[j + 1]);
            if (sequence[0][j] == sequence[1][i] && 
                    table[j + 1] <= previous[j])
                table[j + 1] = previous[j] + 1;
        }
    }
    return table[size[0]];
}

/* Main function */
int main() {
    int test = 1;
    while (scanf("%d %d", &size[0], &size[1]) != EOF && size[0] > 0) {
        int i, k;
        for (k = 0; k < 2; k++)
            for (i = 0; i < size[k]; i++)
                assert(scanf("%d", &sequence[k][i]) != EOF);
        printf("Twin Towers #%d\nNumber of Tiles  %d\n\n", test++, lcs());
    }
    return EXIT_SUCCESS;
}
