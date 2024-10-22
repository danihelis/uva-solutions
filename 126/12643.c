/* 12643
 * Tennis Rounds
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
    int a, b, i;
    while (scanf("%*d %d %d\n", &a, &b) != EOF) {
        for (i = 0; a != b; i++) {
            a = (a - 1) / 2 + 1, b = (b - 1) / 2 + 1;
        }
        printf("%d\n", i);
    }
    return EXIT_SUCCESS;
}
