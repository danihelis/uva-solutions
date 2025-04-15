/* 155
 * All Squares
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CENTER  1024

/* Compute the number of squares in a point */
int number_squares(int k, int px, int py) {
    int x = CENTER, y = CENTER, squares = 0;
    while (k > 0) {
        if (px >= x - k && px <= x + k && py >= y - k && py <= y + k) squares++;
        if (x == px || y == py) break;
        x += px < x ? -k : k;
        y += py < y ? -k : k;
        k /= 2;
    }
    return squares;
}

/* Main function */
int main() {
    int k, x, y;
    while (scanf("%d %d %d", &k, &x, &y) == 3 && k > 0) {
        printf("%3d\n", number_squares(k, x, y));
    }
    return EXIT_SUCCESS;
}
