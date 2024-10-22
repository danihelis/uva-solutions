/* 10931
 * Parity
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BITS    32

/* Main function */
int main() {
    unsigned int n;
    while (scanf("%u", &n) != EOF && n > 0) {
        char stack[MAX_BITS];
        int top = 0, parity = 0;
        while (n > 0) {
            stack[top++] = n % 2;
            parity += n % 2;
            n >>= 1;
        }
        printf("The parity of ");
        for (top--; top >= 0; top--) {
            printf("%d", stack[top]);
        }
        printf(" is %d (mod 2).\n", parity);
    }
    return 0;
}
