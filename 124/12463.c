/* 12463
 * Little Nephew
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
    int a, b, c, d, e;
    while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) != EOF && a > 0) {
        int r = a * b * c * d * d * e * e;
        printf("%d\n", r);
    }
    return EXIT_SUCCESS;
}
