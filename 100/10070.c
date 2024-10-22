/* 10070
 * Leap Year or Not Leap Year and ...
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  10000
#define MODULO      (660 * 400)

/* Main function */
int main() {
    char *c, string[MAX_STRING], first = 1;
    while (scanf(" %s", string) != EOF) {
        int year, leap, h, b;
        for (year = 0, c = string; *c != 0; c++)
            year = (year * 10 + *c - '0') % MODULO;
        leap = year % 4 == 0 && (year % 400 == 0 || year % 100 != 0);
        h = year % 15 == 0, b = year % 55 == 0 && leap;
        (first ? (first = 0) : printf("\n"));
        if (leap)
            printf("This is leap year.\n");
        if (h)
            printf("This is huluculu festival year.\n");
        if (b)
            printf("This is bulukulu festival year.\n");
        if (!leap && !h && !b)
            printf("This is an ordinary year.\n");
    }
    return EXIT_SUCCESS;
}
