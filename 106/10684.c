/* 10684
 * The jackpot
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
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int value, maximum = 0, current = 0;
        for (; n > 0; n--) {
            assert(scanf("%d", &value) != EOF);
            current += value;
            if (current > maximum) {
                maximum = current;
            }
            if (current < 0) {
                current = 0;
            }
        }
        if (maximum == 0) {
            printf("Losing streak.\n");
        }
        else {
            printf("The maximum winning streak is %d.\n", maximum);
        }
    }
    return 0;
}
