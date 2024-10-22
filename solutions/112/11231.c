/* 11231
 * Black and white painting
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int r, c, w;
    while (scanf("%d %d %d", &r, &c, &w) != EOF && r > 0) {
        long t;
        r -= 7, c -= 7;
        t = (r / 2) * (c / 2) * 2;
        t += (r % 2 == 1 ? c / 2 : 0) + (c % 2 == 1 ? r / 2 : 0);
        t += (r % 2 == 1 && c % 2 == 1 && w ? 1 : 0);
        printf("%ld\n", t);
    }
    return 0;
}
