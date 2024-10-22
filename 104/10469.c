/* 10469
 * To Carry or not to Carry
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
    long a, b;
    while (scanf("%ld %ld", &a, &b) != EOF) {
        long sum = a ^ b;
        printf("%ld\n", sum);
    }
    return 0;
}
