/* 706
 * LCD Display
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DIGITS  10
#define MAX_STRING  10
#define NUM_BLOCKS  3

char format[NUM_DIGITS][MAX_STRING] = {
    "-|| ||-", "  |  | ", "- |-| -", "- |- |-", " ||- | ",
    "-| - |-", "-| -||-", "- |  | ", "-||-||-", "-||- |-"};

#define PRINT_TRACE(symbol, size)  do { \
        int _i; \
        for (_i = 0; _i < size; _i++) \
            printf("%c", symbol); \
    } while (0)

/* Print the display of a number sequence */
void display(char *sequence, int size) {
    int k, i, digit;
    char *s;
    for (k = 0; k < NUM_BLOCKS; k++) {
        for (s = sequence; *s != 0; s++) {
            digit = *s - '0';
            printf(" ");
            PRINT_TRACE(format[digit][k * 3], size);
            printf(" %c", *(s + 1) == 0 ? '\n' : ' ');
        }
        if (k < NUM_BLOCKS - 1) {
            for (i = 0; i < size; i++) {
                for (s = sequence; *s != 0; s++) {
                    digit = *s - '0';
                    printf("%c", format[digit][k * 3 + 1]);
                    PRINT_TRACE(' ', size);
                    printf("%c%c", format[digit][k * 3 + 2], *(s + 1) == 0 ? '\n' : ' ');
                }
            }
        }
    }
    printf("\n");
}

/* Main function */
int main() {
    int size;
    char sequence[MAX_STRING];
    while (scanf("%d %s", &size, sequence) != EOF && size > 0) {
        display(sequence, size);
    }
    return 0;
}
