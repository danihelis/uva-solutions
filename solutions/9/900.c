/* 900
 * Brick Wall Patterns
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WIDTH   50

/* Main function */
int main() {
    int i;
    long comb[MAX_WIDTH];
    comb[0] = 1, comb[1] = 2;
    for (i = 2; i < MAX_WIDTH; i++) {
        comb[i] = comb[i - 1] + comb[i - 2];
    }
    while (scanf("%d", &i) != EOF && i > 0) {
        printf("%ld\n", comb[i - 1]);
    }
    return 0;
}
