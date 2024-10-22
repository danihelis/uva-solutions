/* 10077
 * The Stern-Brocot Number System
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    long num, den;
} fraction_t, *fraction_p;

/* Main function */
int main() {
    fraction_t goal;
    while (scanf("%ld %ld", &goal.num, &goal.den) != EOF && !(goal.num == 1 && goal.den == 1)) {
        fraction_t start = {0, 1}, end = {1, 0}, middle;
        long comparison = 1;
        while (comparison != 0) {
            middle.num = start.num + end.num, middle.den = start.den + end.den;
            comparison = goal.num * middle.den - goal.den * middle.num;
            if (comparison < 0) {
                printf("L");
                end = middle;
            }
            else if (comparison > 0) {
                printf("R");
                start = middle;
            }
        }
        printf("\n");
    }    
    return 0;
}
