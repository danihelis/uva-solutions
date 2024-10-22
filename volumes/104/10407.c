/* 10407
 * Simple division
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ABS_DIFF(x, y)  ((x) < (y) ? (y) - (x) : (x) - (y))

/* Greatest common divisor */
int gcd(int a, int b) {
    int m = a % b;
    while (m != 0) {
        a = b;
        b = m;
        m = a % b;
    }
    return b;
}

/* Main function */
int main() {
    int n, m, g, v;
    while (scanf("%d", &n) != EOF && n != 0) {
        g = 0;
        while (scanf("%d", &m) != EOF && m != 0) {
            if (n != m) {
                g = (g == 0 ? ABS_DIFF(n, m) : gcd(g, ABS_DIFF(n, m)));
                n = m;
            }
        }
        printf("%d\n", g);
    }
    return 0;
}
