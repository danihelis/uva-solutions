/* 12646
 * Zero or One
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
    int a, b, c, d;
    while (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (a + b + c == 0 || a + b + c == 3)
            printf("*\n");
        else { 
            d = a + b + c == 1 ? 1 : 0;
            printf("%c\n", a == d ? 'A' : b == d ? 'B' : 'C');
        }
    }
    return EXIT_SUCCESS;
}
