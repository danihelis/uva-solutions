/* 389
 * Basically Speaking
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  7
#define MAX_STRING  (MAX_DIGITS + 2)

/* Main function */
int main() {
    char input[MAX_STRING], output[MAX_STRING];
    int base_from, base_to;
    output[MAX_DIGITS] = 0;
    while (scanf(" %s %d %d", input, &base_from, &base_to) != EOF) {
        long number;
        char *p;
        for (p = input, number = 0; *p != 0; p++)
            number = number * base_from + (isdigit(*p) ? *p - '0' :
                    *p - 'A' + 10);
        if (number == 0) {
            printf("%7d\n", 0);
            continue;
        }
        for (p = output + MAX_DIGITS - 1; p >= output; p--) {
            if (number == 0)
                *p = ' ';
            else {
                int digit = number % base_to;
                *p = (digit < 10 ? '0' + digit : 'A' + digit - 10);
                number /= base_to;
            }
        }
        printf("%7s\n", number > 0 ? "ERROR" : output);
    }

    return EXIT_SUCCESS;
}
