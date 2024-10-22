/* 591
 * Box of Bricks
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BOXES   100

/* Main function */
int main() {
    int test = 0, n, box[MAX_BOXES];
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, sum, result;
        for (i = 0, sum = 0; i < n; i++) {
            assert(scanf("%d", &box[i]) != EOF);
            sum += box[i];
        }
        for (i = 0, result = 0, sum /= n; i < n; i++) {
            result += (box[i] > sum ? box[i] - sum : 0);
        }
        printf("Set #%d\nThe minimum number of moves is %d.\n\n",
                ++test, result);
    }
    return 0;
}
