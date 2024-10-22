/* 12545
 * Bits Equalizer
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  102
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        char input[MAX_STRING], output[MAX_STRING], *i, *o;
        int mis_zeroes, mis_ones, wild_zeroes, wild_ones, total;
        assert(scanf(" %s %s", input, output) != EOF);
        mis_zeroes = mis_ones = wild_zeroes = wild_ones = 0;
        for (i = input, o = output; *i != 0; i++, o++) {
            switch (*i) {
                case '?':
                    wild_zeroes += *o == '0' ? 1 : 0;
                    wild_ones += *o == '1' ? 1 : 0;
                    break;
                case '0': mis_ones += *o == '1' ? 1 : 0; break;
                case '1': mis_zeroes += *o == '0' ? 1 : 0; break;
            }
        }
        total = wild_zeroes + wild_ones;
        if (mis_ones + wild_ones < mis_zeroes) total = -1;
        else total += MAX(mis_zeroes, mis_ones);
        printf("Case %d: %d\n", test, total);
    }

    return EXIT_SUCCESS;
}
