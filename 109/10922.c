/* 10922
 * 2 the 9s
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 1005

/* Computes 9-degree, or -1 if not multiple of 9 */
int degree(int n) {
    int sum, degree = 1;
    while (n > 9) {
        for (sum = 0; n > 0; n /= 10)
            sum += n % 10;
        n = sum, degree++;
    }
    return n == 9 ? degree : -1;
}

/* Main function */
int main() {
    char *c, number[MAX_STRING];
    while (scanf(" %s", number) != EOF && strcmp(number, "0") != 0) {
        int sum, deg;
        for (sum = 0, c = number; *c != 0; c++)
            sum += *c - '0';
        deg = degree(sum);
        printf("%s is ", number);
        if (deg > 0)
            printf("a multiple of 9 and has 9-degree %d.\n", deg);
        else
            printf("not a multiple of 9.\n");
    }
    return EXIT_SUCCESS;
}
