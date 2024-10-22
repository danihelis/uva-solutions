/* 594
 * One Little, Two Little, Three Little Endians
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int i, n, revert;
    while (scanf("%d", &n) != EOF) {
        for (revert = 0, i = 0; i < 4; i++) {
            revert |= ((n >> (8 * i)) & 0xFF) << (24 - 8 * i);
        }
        printf("%d converts to %d\n", n, revert);
    }
    return 0;
}
