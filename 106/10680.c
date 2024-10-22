/* 10680
 * LCM
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000000
#define MASK    10000000000

int lcd[MAX_N];

/* Compute LCD using sieve */
void compute_lcd() {
    int i, j, table[MAX_N + 2];
    long value;
    for (i = 1; i <= MAX_N; i++)
        table[i] = i;
    for (i = 2; i <= MAX_N; i++)
        if (table[i] > 1)
            for (j = i * 2; j <= MAX_N; j += i)
                table[j] /= table[i];
    for (i = 1, value = 1; i <= MAX_N; i++) {
        if (table[i] > 1) {
            value *= table[i];
            while (value % 10 == 0)
                value /= 10;
            value %= MASK;
        }
        lcd[i - 1] = value % 10;
    }
}

/* Main function */
int main() {
    int n;
    compute_lcd();
    while (scanf("%d", &n) != EOF && n > 0)
        printf("%d\n", lcd[--n]);
    return EXIT_SUCCESS;
}
