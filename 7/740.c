/* 740
 * Baudot Data Communication Code
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      85
#define MAX_SHITFS      2
#define NUM_BITS        5
#define SHIFT_UP        0x1f
#define SHITF_DOWN      0x1b

/* Main function */
#define READ(s)     (fgets(s, MAX_STRING, stdin) != NULL)
int main() {
    char code[MAX_SHITFS][MAX_STRING], line[MAX_STRING];
    assert(READ(code[0]) && READ(code[1]));
    while (READ(line)) {
        char *p, shift;
        for (p = line, shift = 0; isdigit(*p); ) {
            int i, value;
            for (i = 0, value = 0; i < NUM_BITS; i++, p++) {
                value = (value << 1) + *p - '0';
            }
            if (value == SHIFT_UP || value == SHITF_DOWN) {
                shift = (value == SHIFT_UP ? 1 : 0);
            }
            else {
                printf("%c", code[(int) shift][value]);
            }
        }
        printf("\n");
    }
    return 0;
}
