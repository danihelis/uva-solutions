/* 11827
 * Maximum GCD
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     100
#define MAX_LINE        (MAX_NUMBERS * 10)
#define SEP             " \t\n"

/* GCD */
int gcd(int a, int b) {
    while (b > 0) {
        int mod = a % b;
        a = b;
        b = mod;
    }
    return a;
}

/* Main function */
int main() {
    char line[MAX_LINE], *n;
    int num_tests;
    assert(fgets(line, MAX_LINE, stdin) != NULL);
    for (num_tests = atoi(line); num_tests > 0; num_tests--) {
        int i, j, number[MAX_NUMBERS], best;
        assert(fgets(line, MAX_LINE, stdin) != NULL);
        for (n = strtok(line, SEP), i = best = 0; n != NULL; 
                n = strtok(NULL, SEP), i++) {
            number[i] = atoi(n);
            for (j = 0; j < i; j++) {
                int g = gcd(number[i], number[j]);
                if (g > best)
                    best = g;
            }
        }
        printf("%d\n", best);
    }
    return EXIT_SUCCESS;
}
