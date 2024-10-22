/* 10323
 * Factorial! You Must be Kidding!!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define UNDER       10000
#define OVER        6227020800
#define MAX_FACT    13

/* This problem is really bogus! It follows a very flawed logic that
 * asserts that 0! = 1 and, since 0! = 0 * -1!, -1! must be infinite.
 * Likewise -2! = -2 * -1!, and thus is minus infinite.
 */

/* Main function */
int main() {
    long factorial[MAX_FACT];
    int minimum, i;
    for (i = 2, factorial[0] = 1, minimum = 0; i <= MAX_FACT; i++) {
        factorial[i - 1] = i * factorial[i - 2];
        if (factorial[i - 1] < UNDER)
            minimum = i;
    }
    while (scanf("%d", &i) != EOF)
        if ((i >= 0 && i <= minimum) || (i < 0 && abs(i) % 2 == 0))
            printf("Underflow!\n");
        else if ((i >= 0 && i > MAX_FACT) || (i < 0 && abs(i) % 2 == 1))
            printf("Overflow!\n");
        else
            printf("%ld\n", factorial[i - 1]);
    return EXIT_SUCCESS;
}
