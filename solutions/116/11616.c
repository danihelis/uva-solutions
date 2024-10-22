/* 11616
 * Roman Numerals
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE 100

/* Convert arabic to roman */
void to_roman(char number[]) {
    static char unit[4] = {'I', 'X', 'C', 'M'};
    static char fifth[4] = {'V', 'L', 'D', '\0'};
    int i, j, size = strlen(number);
    for (i = 0; i < size; i++) {
        int house = size - i - 1;
        if (number[i] == '4' || number[i] == '9') {
            printf("%c%c", unit[house], (number[i] == '4' ? fifth[house] : unit[house + 1]));
            continue;
        }
        if (number[i] >= '5') {
            printf("%c", fifth[house]);
            number[i] -= 5;
        }
        for (j = 0; j < number[i] - '0'; j++) {
            printf("%c", unit[house]);
        }
    }
    printf("\n");
}

/* Convert roman to arabic */
void to_arabic(char number[]) {
    char *current;
    int total = 0, last = 0;
    for (current = number; *current != 0; current++) {
        int value = 0;
        switch (*current) {
            case 'I': value = 1; break;
            case 'V': value = 5; break;
            case 'X': value = 10; break;
            case 'L': value = 50; break;
            case 'C': value = 100; break;
            case 'D': value = 500; break;
            case 'M': value = 1000; break;
        }
        if (last > 0 && last < value) {
            value -= 2 * last;
        }
        total += value;
        last = value;
    }
    printf("%d\n", total);
}

/* Main function */
int main() {
    char number[MAX_SIZE];
    while (scanf(" %s", number) != EOF) {
        if (isdigit(number[0])) {
            to_roman(number);
        }
        else {
            to_arabic(number);
        }
    }
    return 0;
}
