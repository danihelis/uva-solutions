/* 913
 * Joana and the Odd Numbers
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
    long n, s;
    while (scanf("%ld", &n) != EOF) {
        n++;
        s = 3 * n * n / 2 - 9;
        printf("%ld\n", s);
    }
    return 0;
}
