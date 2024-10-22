/* 10079
 * Pizza Cutting
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
    long n;
    while (scanf("%ld", &n) != EOF && n >= 0) {
        printf("%ld\n", n * (n + 1) / 2 + 1);
    }
    return 0;
}
