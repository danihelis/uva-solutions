/* 10038
 * Jolly Jumpers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     3000
#define ABS_DIFF(x, y)  (x < y ? y - x : x - y)

/* Main function */
int main() {
    int i, n, last, current;
    char jolly[MAX_NUMBERS], is_jolly;
    while (scanf("%d", &n) != EOF) {
        memset(jolly, 0, n);
        for (i = 0, is_jolly = 1, last = 0; i < n; i++) {
            assert(scanf("%d", &current) != EOF);
            if (i > 0 && is_jolly) {
                int diff = ABS_DIFF(current, last);
                is_jolly = (diff < n) && !jolly[diff];
                if (is_jolly) {
                    jolly[diff] = 1;
                }
            }
            last = current;
        }
        printf("%s\n", (is_jolly ? "Jolly" : "Not jolly"));
    }
    return 0;
}
