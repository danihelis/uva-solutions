/* 231
 * Testing the CATCHER
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SEQUENCE 1000000

/* Main function */
int main() {
    int sequence[MAX_SEQUENCE];
    int test = 0, input, length;
    while (scanf("%d", &input) != EOF && input != -1) {
        sequence[0] = input;
        length = 1;
        while (scanf("%d", &input) != EOF && input != -1) {
            int i;
            for (i = length - 1; i >= 0 && sequence[i] < input; i--)
                ;
            sequence[i + 1] = input;
            if (i == length - 1) {
                assert(length < MAX_SEQUENCE);
                length++;
            }
        }
        printf("%sTest #%d:\n  maximum possible interceptions: %d\n", (test > 0 ? "\n" : ""),
                test + 1, length);
        test++;
    }
    return 0;
}
