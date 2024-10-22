/* 1586
 * Molar mass
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100

/* Decode chemical formula */
int decode(char *formula) {
    int sum, multi, mass;
    char *s;
    for (sum = multi = mass = 0, s = formula; *s != 0; s++) {
        if (isdigit(*s))
            multi = 10 * multi + *s - '0';
        else {
            sum += (multi > 0 ? multi : 1) * mass;
            multi = 0;
            switch (*s) {
                case 'C': mass = 12010; break;
                case 'H': mass =  1008; break;
                case 'O': mass = 16000; break;
                case 'N': mass = 14010; break;
            }
        }
    }
    sum += (multi > 0 ? multi : 1) * mass;
    return sum;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        char formula[MAX_STRING];
        int mass;
        assert(scanf(" %s", formula) == 1);
        mass = decode(formula);
        printf("%d.%03d\n", mass / 1000, mass % 1000);
    }
    return EXIT_SUCCESS;
}
