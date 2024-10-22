/* 213
 * Message Decoding
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CODES       256
#define SEGMENT_SIZE    3

/* Read next `length` bits and return binary value */
int read_next(int length) {
    int value = 0;
    char bit;
    while (length-- > 0) {
        assert(scanf(" %c", &bit) != EOF);
        value = (value << 1) + bit - '0';
    }
    return value;
}

/* Main function */
int main() {
    char header[MAX_CODES];
    char first = 1;
    while (scanf(first ? "%[^\n]" : "%*[\n]%[^\n]", header) != EOF) {
        int length;
        while ((length = read_next(SEGMENT_SIZE)) > 0) {
            int value, end, index;
            end = (1 << length) - 1, index = (1 << length) - length - 1;
            while ((value = read_next(length)) != end) {
                printf("%c", header[index + value]);
            }
        }
        printf("\n");
        first = 0;
    }
    return EXIT_SUCCESS;
}
