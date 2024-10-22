/* 10473
 * Simple Base Conversion
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    char input[30];
    while (scanf(" %s", input) != EOF && input[0] != '-') {
        int value;
        assert(sscanf(input, "%i", &value) == 1);
        printf(input[1] == 'x' ? "%d\n" : "0x%X\n", value);
    }
    return EXIT_SUCCESS;
}
