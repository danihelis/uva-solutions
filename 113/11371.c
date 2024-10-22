/* 11371
 * Number Theory for Newbies
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DIGITS  10

/* Main function */
int main() {
    char digit;
    while (scanf(" %c", &digit) != EOF) {
        int i, j, low_digit, digits[NUM_DIGITS];
        long highest, lowest, difference;
        memset(digits, 0, sizeof (digits));
        low_digit = 10;
        do {
            int d = digit - '0';
            digits[d]++;
            if (d < low_digit && d > 0)
                low_digit = d;
        } while (scanf("%c", &digit) != EOF && isdigit(digit));
        for (i = NUM_DIGITS - 1, highest = 0; i >= 0; i--)
            for (j = 0; j < digits[i]; j++)
                highest = highest * 10 + i;
        for (i = 0, digits[low_digit]--, lowest = low_digit; 
                i < NUM_DIGITS; i++)
            for (j = 0; j < digits[i]; j++)
                lowest = lowest * 10 + i;
        difference = highest - lowest;
        printf("%ld - %ld = %ld = 9 * %ld\n", highest, lowest, 
                difference, difference / 9);
    }
    return EXIT_SUCCESS;
}
