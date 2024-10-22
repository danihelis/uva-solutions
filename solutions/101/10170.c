/* 10170
 * The Hotel with Infinite Rooms
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
    long s, d;
    while (scanf("%ld %ld", &s, &d) != EOF) {
        if (d <= s)
            printf("%ld\n", s);
        else {
            long delta = (2 * s - 1) * (2 * s - 1) + 8 * d;
            long k = (sqrt(delta) - (2 * s + 1)) / 2;
            long n = s * (k + 1) + k * (k + 1) / 2;
            if (n < d)
                k++;
            printf("%ld\n", k + s);
        }
    }
    return EXIT_SUCCESS;
}
