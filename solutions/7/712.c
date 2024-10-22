/* 712
 * S-Trees
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       7
#define MAX_DIM     (1 << MAX_N)
#define MAX_STR     (MAX_DIM + 2)

int pos[MAX_N];
char output[MAX_STR];
int n;

/* Decode function */
char decode(char *input) {
    int i, index, band;
    for (index = 0, band = 1, i = n - 1; i >= 0; i--, band *= 2)
        if (input[pos[i]] == '1')
            index += band;
    assert(index >= 0 && index < (1 << n));
    return output[index];
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        int i, k;
        for (i = 0; i < n; i++) {
            assert(scanf(" x%d", &k) == 1);
            pos[i] = --k;
        }
        assert(scanf(" %s %d", output, &i) == 2);
        printf("S-Tree #%d:\n", ++test);
        for (; i > 0; i--) {
            char input[MAX_STR];
            assert(scanf( "%s", input) == 1);
            putchar(decode(input));
        }
        printf("\n\n");
    }
    return EXIT_SUCCESS;
}
