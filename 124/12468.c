/* 12468
 * Zapping
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
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF && a != -1) {
        int d1 = (100 + a - b) % 100, d2 = (100 + b - a) % 100;
        printf("%d\n", d1 < d2 ? d1 : d2);
    }
    return EXIT_SUCCESS;
}
