/* 11236
 * Grocery store
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       2000
#define M           1000000
#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define PRINT(n,s)  printf("%ld.%02ld%s", n / 100, n % 100, \
                            s ? " " : "\n")

/* Main function */
int main() {
    long a, b, c, d;
    for (a = 1; a <= MAX_N; a++)
        for (b = a; b <= MAX_N; b++) {
            long p = a * b, s = a + b, low, high, limit;
            if (p > 20000 || s > 600)
                break;
            limit = M / p + 1;
            low = MAX(b, limit);
            high = (MAX_N - s) / 2;
            for (c = low; c <= high; c++) {
                long num = M * (s + c), den = p * c - M;
                if (num % den == 0) {
                    d = num / den;
                    if (d > MAX_N || d < c || s + d + c > 2000)
                        continue;
                    PRINT(a, 1);
                    PRINT(b, 1);
                    PRINT(c, 1);
                    PRINT(d, 0);
                }
            }
        }
    return EXIT_SUCCESS;
}
