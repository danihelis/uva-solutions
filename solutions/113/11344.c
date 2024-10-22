/* 11344
 * The Huge One
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE        27720
#define MAX_STRING  1010

/* Read */
int read(char *s) {
    int n = 0;
    for (; *s != 0; s++)
        n = (n * 10 + *s - '0') % BASE;
    return n;
}

/* Greatest common divisor */
int gcd(int a, int b) {
    while (b > 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

/* Compute Longest Common Divisor */
int compute_lcd() {
    int n, lcd, v;
    assert(scanf("%d", &n) != EOF);
    for (lcd = 1; n > 0; n--) {
        assert(scanf("%d", &v) != EOF);
        lcd = lcd / gcd(v, lcd) * v;
    }
    return lcd;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char input[MAX_STRING];
        int n, lcd;
        assert(scanf(" %s", input) != EOF);
        n = read(input);
        lcd = compute_lcd();
        printf("%s - %s.\n", input, n % lcd == 0 ? "Wonderful" : "Simple");
    }
    return EXIT_SUCCESS;
}
