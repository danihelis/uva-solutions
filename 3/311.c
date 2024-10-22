/* 311
 * Packets
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int i, used, free, boxes, products[6];
    while (!feof(stdin)) {
        for (i = used = 0; i < 6; i++) {
            assert(scanf("%d", &products[i]) == 1);
            used |= products[i] > 0;
        }
        if (!used)
            break;

        /* Fit large boxes and fill 1x1's */
        for (boxes = 0, i = 6; i >= 4; i--) {
            boxes += products[i - 1];
            free = (36 - i * i) * products[i - 1];
            if (i <= 4) {
                /* Fill also 2x2's */
                used = MIN(5 * products[i - 1], products[1]);
                products[1] -= used;
                free -= used * 4;
            }
            products[0] -= MIN(products[0], free);
        }
        /* Fit 3x3's */
        boxes += products[2] / 4;
        if (products[2] % 4 != 0) {
            int in = products[2] % 4;
            boxes++;
            free = 36 - 9 * in;
            used = MIN(in == 1 ? 5 : in == 2 ? 3 : 1, products[1]);
            products[1] -= used, free -= 4 * used;
            products[0] -= MIN(products[0], free);
        }
        /* Fit 2x2's */
        boxes += products[1] / 9;
        if (products[1] % 9 != 0) {
            boxes++;
            free = 36 - 4 * (products[1] % 9);
            products[0] -= MIN(products[0], free);
        }
        /* Fit remaining 1x1's */
        boxes += (products[0] + 35) / 36;

        printf("%d\n", boxes);
    }
    return EXIT_SUCCESS;
}
