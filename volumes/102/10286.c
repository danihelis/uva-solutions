/* 10286
 * Trouble with a Pentagon
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define PI  3.141592653589793238

/* Main function */
int main() {
    double side, ratio = sin(3 * PI / 5) / sin(7 * PI / 20);
    while (scanf("%lf", &side) != EOF) {
        printf("%.10f\n", side * ratio);
    }
    return 0;
}
