/* 138
 * Street Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_OUTPUTS     10
#define START_VALUE     8
#define SPEED_UP        5.8

/* Main function */
int main() {
    long n, k, c, sum;
    for (n = START_VALUE, c = 0; c < NUM_OUTPUTS; n++) {
        sum = (n * n + n) / 2;
        k = sqrt(sum);
        if (k * k == sum) {
            printf("%10ld%10ld\n", k, n);
            c++;
            n *= SPEED_UP;
        }
    }
    return 0;
}
