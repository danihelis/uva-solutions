/* 10019
 * Funny Encryption Method
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Count the number of 1's in binary representation of number */
int binary_ones(int number) {
    int total = 0;
    while (number > 0) {
        total += number % 2;
        number /= 2;
    }
    return total;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char input[100];
        unsigned int i, number;
        assert(scanf(" %s", input) != EOF);
        for (i = 0; i < 2; i++) {
            assert(sscanf(input, i == 0 ? "%u" : "%x", &number) == 1);
            printf("%d%c", binary_ones(number), i == 0 ? ' ' : '\n');
        }
    }
    return 0;
}
