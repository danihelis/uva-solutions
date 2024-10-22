/* 386
 * Perfect Cubes
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER      200
#define LIMIT_FACTOR    0.7

#define CUBE(x)         ((x) * (x) * (x))
/* Main function */
int main() {
    int a, b, c, a3, b3, c3, n, n3, n3p, n3pp;
    for (n = 6; n <= MAX_NUMBER; n++) {
        int limit;
        for (a = 2, limit = n * LIMIT_FACTOR, n3 = CUBE(n); a <= limit; a++) {
            a3 = CUBE(a);
            n3p = n3 - a3;
            for (b = a, b3 = CUBE(a), n3p = n3 - a3; 2 * b3 <= n3p; b3 = CUBE(b)) {
                for (c = b, c3 = CUBE(b), n3pp = n3p - b3; c3 < n3pp; c3 = CUBE(c)) {
                    c++;
                }
                if (c3 == n3pp) {
                    printf("Cube = %d, Triple = (%d,%d,%d)\n", n, a, b, c);
                }
                b++;
            }
        }
    }
    return 0;
}
