/* 12114
 * Bachelor Arithmetic
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
    int b, s, test = 0;
    while (scanf("%d %d", &b, &s) == 2 && b > 0)
        printf("Case %d: :-%c\n", ++test,
            b == 1 ? '\\' : s >= b ? '|' : '('); 
    return EXIT_SUCCESS;
}
