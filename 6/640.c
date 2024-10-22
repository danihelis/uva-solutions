/* 640
 * Self Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 1000000

char self[MAX_NUMBERS];

/* Compute the digitation of a number */
int digitation(int n) {
    int d = n;
    while (n > 0) {
        d += n % 10;
        n /= 10;
    }
    return d;
}

/* Main function */
int main() {
    int i;
    memset(self, 1, MAX_NUMBERS);
    for (i = 0; i < MAX_NUMBERS; i++) {
        int d = digitation(i + 1);
        if (d <= MAX_NUMBERS) {
            self[d - 1] = 0;
        }
    }
    for (i = 0; i < MAX_NUMBERS; i++) {
        if (self[i]) {
            printf("%d\n", i + 1);
        }
    }
    return 0;
}
