/* 10035
 * Primary Arithmetic
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
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF && (a > 0 || b > 0)) {
        int carries = 0, carry = 0;
        while (a > 0 || b > 0) {
            carry = ((a % 10) + (b % 10) + carry) / 10;
            carries += (carry == 0 ? 0 : 1);
            a /= 10, b /= 10;
        }
        if (carries == 0) {
            printf("No");
        }
        else {
            printf("%d", carries);
        }
        printf(" carry operation%s.\n", (carries > 1 ? "s" : ""));
    }
    return 0;
}
