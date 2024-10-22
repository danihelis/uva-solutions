/* 100
 * The 3n + 1 problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

/* Determine the cycle-length of a number */
int cycle(int n) {
    int steps = 1;
    while (n > 1) {
        n = (n % 2 == 0 ? n / 2 : 3 * n + 1);
        steps++;
    }
    return steps;
}

/* Main function */
int main() {
    int i, j;
    while (scanf("%d %d", &i, &j) != EOF) {
        int n, maximum;
        for (n = MIN(i, j), maximum = 0; n <= MAX(i, j); n++) {
            int length = cycle(n);
            if (length > maximum) {
                maximum = length;
            }
        }
        printf("%d %d %d\n", i, j, maximum);
    }
    return 0;
}
