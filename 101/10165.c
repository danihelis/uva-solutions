/* 10165
 * Stone Game
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
    while (scanf("%d", &n) == 1 && n > 0) {
        /* It's a nim-sum game, whose solution is this */
        int value, xor_sum = 0;
        while (n-- > 0) {
            assert(scanf("%d", &value) == 1);
            xor_sum ^= value;
        }
        printf("%s\n", xor_sum ? "Yes" : "No");        
    }
    return EXIT_SUCCESS;
}
