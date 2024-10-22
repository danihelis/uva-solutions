/* 12704
 * Little Masters
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
    int x, y, r;
    assert(scanf("%*d") != EOF);
    while (scanf("%d %d %d", &x, &y, &r) != EOF) {
        double dist = sqrt(x * x + y * y);
        printf("%.2f %.2f\n", r - dist, r + dist);
    }
    return EXIT_SUCCESS;
}
