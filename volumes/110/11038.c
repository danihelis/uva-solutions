/* 11038
 * How Many O's?
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS      11

long table_nine[MAX_DIGITS];
long table_nine_padding[MAX_DIGITS];

/* Return the number of zeros for all numbers from 0 to number */
long get_zeroes(long number, int decimal, char with_padding) {
    long mask, head, remaining;
    int i;

    if (decimal == 0) return 1;

    for (i = 0, mask = 1; i < decimal; i++) {
        mask *= 10;
    }
    head = number / mask;
    remaining = number % mask;

    if (!with_padding) {
        assert(head > 0);
        return table_nine[decimal - 1] +
            (head - 1) * table_nine_padding[decimal - 1] +
            get_zeroes(remaining, decimal - 1, 1);
    }
    if (head == 0) {
        return remaining + 1 + get_zeroes(remaining, decimal - 1, 1);
    }
    return mask + head * table_nine_padding[decimal - 1] +
        get_zeroes(remaining, decimal - 1, 1);
}

/* Fill table for `get_zeroes` with only digit 9 */
void fill_table_nine() {
    long number = 0;
    int i;
    for (i = 0; i < MAX_DIGITS; i++) {
        number = number * 10 + 9;
        table_nine_padding[i] = get_zeroes(number, i, 1);
        table_nine[i] = get_zeroes(number, i, 0);
    }
}

/* Main function */
int main() {
    long a, b;
    fill_table_nine();

    while (scanf("%ld %ld", &a, &b) == 2 && a >= 0) {
        long zeroes[2];
        int i;

        for (i = 0; i < 2; i++) {
            long number = i == 0 ? a - 1: b;
            int decimal;
            if (number < 0) zeroes[i] = 0;
            else {
                decimal = 0;
                while (number >= 10) {
                    number /= 10;
                    decimal++;
                }
                zeroes[i] = get_zeroes(i == 0 ? a - 1 : b, decimal, 0);
            }
        }
        printf("%ld\n", zeroes[1] - zeroes[0]);
    }
    return EXIT_SUCCESS;
}
