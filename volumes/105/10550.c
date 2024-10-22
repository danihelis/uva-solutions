/* 10550
 * Combination Lock
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define FULL_TURN   360
#define DEG(x)      (9 * (x))


/* Main function */
int main() {
    int z, a, b, c;
    while (scanf("%d %d %d %d", &z, &a, &b, &c) != EOF && (a != 0 || b != 0 || c != 0)) {
        int degrees = FULL_TURN * 3;
        degrees += DEG(z - a) + (a <= z ? 0 : FULL_TURN);
        degrees += DEG(b - a) + (b >= a ? 0 : FULL_TURN);
        degrees += DEG(b - c) + (c <= b ? 0 : FULL_TURN);
        printf("%d\n", degrees);
    }
    return 0;
}
