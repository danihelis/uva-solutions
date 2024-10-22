/* 455
 * Periodic Strings
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char string[MAX_STRING];
        int i, k, period, length, equal;
        assert(scanf(" %s", string) != EOF);
        length = strlen(string);
        for (period = 1, equal = 0; !equal && period * 2 <= length; 
                period++) {
            if (length % period != 0)
                continue;
            for (i = 0, equal = 1; equal && i < period; i++)
                for (k = i + period; equal && k < length; k += period)
                    equal = string[i] == string[k];
        }
        printf("%d\n%s", equal ? --period : length, 
                num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
