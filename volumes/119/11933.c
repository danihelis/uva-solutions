/* 11933
 * Splitting Numbers
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
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int d = 0, a = 0, b = 0, turn_a = 1;
        while (n > 0) {
            if (n % 2 == 1) {
                if (turn_a) {
                    a |= 1 << d;
                }
                else {
                    b |= 1 << d;
                }
                turn_a = !turn_a;
            }
            d++;
            n >>= 1;
        }
        printf("%d %d\n", a, b);
    }
    return 0;
}
