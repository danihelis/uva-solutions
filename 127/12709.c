/* 12709
 * Falling Ants
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
    int n, l, w, h, max_height, max_weight;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (max_height = max_weight = 0; n > 0; n--) {
            assert(scanf("%d %d %d", &l, &w, &h) != EOF);
            if (h >= max_height) {
                int weight = l * w * h;
                if (h > max_height || weight > max_weight) {
                    max_height = h, max_weight = weight;
                }
            }
        }
        printf("%d\n", max_weight);
    }
    return EXIT_SUCCESS;
}
