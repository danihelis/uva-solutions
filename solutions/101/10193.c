/* 10193
 * All You Need Is Love
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  32

/* Decode string into binary number */
int decode(char *string) {
    int value;
    for (value = 0; *string != 0; string++) {
        value = (value << 1) + *string - '0';
    }
    return value;
}

/* Greatest common divisor */
int gcd(int a, int b) {
    while (b > 0) {
        int old = a;
        a = b;
        b = old % b;
    }
    return a;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        char s1[MAX_STRING], s2[MAX_STRING];
        int n1, n2;
        assert(scanf(" %s %s", s1, s2) != EOF);
        n1 = decode(s1), n2 = decode(s2);
        printf("Pair #%d: %s!\n", test, gcd(n1, n2) > 1 ? "All you need is love" :
                "Love is not all you need");
    }
    return 0;
}
