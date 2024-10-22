/* 11683
 * Laser Sculpture
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
    int height, width;
    while (scanf("%d %d", &height, &width) == 2 && height > 0) {
        int i, count, last, value;
        for (i = 0, count = 0, last = height; i < width; i++) {
            assert(scanf("%d", &value) == 1);
            if (value < last)
                count += last - value;
            last = value;
        }
        printf("%d\n", count);
    }
    return EXIT_SUCCESS;
}
