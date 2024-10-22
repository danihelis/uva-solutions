/* 11150
 * Cola
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BOTTLES 210

int extra[MAX_BOTTLES];

/* Main function */
int main() {
    int n, top;
    extra[0] = 0;
    extra[1] = 0;
    extra[2] = 1;
    top = 2;
    while (scanf("%d", &n) != EOF) {
        for (; top <= n; top++) {
            extra[top] = top / 3 + extra[top / 3 + top % 3];
        }
        printf("%d\n", n + extra[n]);
    }
    return 0;
}
