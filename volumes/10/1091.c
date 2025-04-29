/* 1091
 * Barcodes
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA        150
#define MIN(x,y)        ((x) < (y) ? (x) : (y))
#define MAX(x,y)        ((x) > (y) ? (x) : (y))

#define DASH            10
#define START_END       11
#define INVALID         100
#define INVALID_C       101
#define INVALID_K       102
#define VALID           103

int data[MAX_DATA], size;
int content[MAX_DATA], length;

/* Read data and return success code */
int readbar() {
    int i, k, sum, value;
    int lowest, highest, middle;
    for (i = 0, lowest = 0xFFF; i < size; i++) {
        lowest = MIN(lowest, data[i]);
    }
    middle = lowest * 1.5;
    for (i = 0, lowest = 0xFF, highest = 0; i < size; i++) {
        value = data[i] * (data[i] > middle ? 1 : 2);
        lowest = MIN(lowest, value);
        highest = MAX(highest, value);
    }
    if (highest * 95 > lowest * 105) return INVALID;

    i = length = 0;
    while (i < size) {
        int start_end = i == 0;
        for (k = sum = 0; k < 5; k++, i++) {
            int bit = (i >= size || data[i] > middle) ? 1 : 0;
            sum = (sum << 1) + bit;
        }
        start_end |= i >= size;

        if (i < size && data[i++] > middle) return INVALID;

        value = INVALID;
        switch (sum) {
            case 001: value = 0; break;
            case 021: value = 1; break;
            case 011: value = 2; break;
            case 030: value = 3; break;
            case 005: value = 4; break;
            case 024: value = 5; break;
            case 014: value = 6; break;
            case 003: value = 7; break;
            case 022: value = 8; break;
            case 020: value = 9; break;
            case 004: value = DASH; break;
            case 006: value = START_END; break;
        }

        if (start_end && value != START_END) value = INVALID;
        if (value == INVALID) return INVALID;
        if (!start_end) content[length++] = value;
    }

    if (length < 2) return INVALID;
    for (i = value = 0; i < length - 2; i++) {
        value += (((length - i + 7) % 10) + 1) * content[i];
        value %= 11;
    }
    if (value != content[length - 2]) return INVALID_C;

    for (i = value = 0; i < length - 1; i++) {
        value += (((length - i + 7) % 9) + 1) * content[i];
        value %= 11;
    }
    if (value != content[length - 1]) return INVALID_K;
    return VALID;
}

/* Main function */
int main() {
    int num_tests = 0;
    while (scanf("%d", &size) == 1 && size > 0) {
        int i, j, code, other;
        for (i = 0; i < size; i++) {
            assert(scanf("%d", &data[i]) == 1);
        }
        code = readbar();
        if (code != VALID) {
            for (i = 0, j = size - 1; i < j; i++, j--) {
                int swap = data[i];
                data[i] = data[j];
                data[j] = swap;
            }
            other = readbar();
            code = MAX(other, code);
        }
        printf("Case %d: ", ++num_tests);
        if (code != VALID) {
            printf("bad %s\n", code == INVALID_C ? "C" : code == INVALID_K ?
                    "K": "code");
        } else {
            for (i = 0; i < length - 2; i++) {
                code = content[i];
                printf("%c", code == DASH ? '-' : '0' + code);
            }
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
