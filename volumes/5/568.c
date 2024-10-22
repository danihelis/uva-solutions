/* 568
 * Just the Facts
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VALUE   10000
#define MAX_NUMBERS (MAX_VALUE + 1)

int last_digit[MAX_NUMBERS];
int last_value[MAX_NUMBERS];
int last;

/* Main function */
int main() {
    int n;
    last_value[0] = 1, last_digit[0] = 1, last = 1;
    while (scanf("%d", &n) != EOF) {
        for (; last <= n; last++) {
            long k = last * (long) last_value[last - 1];
            while (k % 10 == 0) {
                k /= 10;
            }
            last_digit[last] = k % 10;
            last_value[last] = k % 1000000;
        }
        printf("%5d -> %d\n", n, last_digit[n]);
    }
    return 0;
}
