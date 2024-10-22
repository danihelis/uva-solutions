/* 11854
 * Egypt
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define SQ(x)           ((x) * (x))

/* Main function */
int main() {
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) != EOF && (a > 0 || b > 0 || c > 0)) {
        int max = MAX(a, b), min1 = MIN(a, b), min2;
        min2 = MIN(max, c);
        max = MAX(max, c);
        printf("%s\n", (SQ(max) == SQ(min1) + SQ(min2)) ? "right" : "wrong");
    }
    return 0;
}
