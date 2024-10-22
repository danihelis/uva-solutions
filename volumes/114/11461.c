/* 11461
 * Square Numbers
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
    int a, b, min, max, total;
    while (scanf("%d %d", &a, &b) != EOF && a > 0) {
        min = (int) sqrt(a), max = (int) sqrt(b);
        total = max - min + (min * min == a ? 1 : 0);
        printf("%d\n", total);                
    }
    return 0;
}
