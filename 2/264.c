/* 264
 * Count on Cantor
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
    int term;
    while (scanf("%d", &term) != EOF) {
        int n = floor(0.5 + sqrt(2.0 * term));
        int base = n * (n - 1) / 2 + 1;
        int num = term - base + 1, den = n - term + base;
        if (n % 2 == 1) {
            int swap = num;
            num = den;
            den = swap;
        }            
        printf("TERM %d IS %d/%d\n", term, num, den);
    }
    return 0;
}
