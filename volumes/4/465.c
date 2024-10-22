/* 465
 * Overflow
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define LIMIT 0x80000000

/* Read a non blank character */
int read_char(char *c) {
    while (!feof(stdin) && isspace(*c = getchar()))
        ;
    return !feof(stdin);
}

/* Read a number from input */
int read_number(unsigned long *value) {
    char c, fit;
    if (!read_char(&c))
        return EOF;
    putchar(c);
    *value = c - '0', fit = 1;
    while (isdigit(c = getchar())) {
        putchar(c);
        if (fit) {
            *value = *value * 10 + c - '0';
            if (*value >= LIMIT)
                fit = 0;
        }
    }
    return fit;
}

/* Main function */
int main() {
    int fit_a, fit_b;
    unsigned long a, b, r;
    char op;
    while ((fit_a = read_number(&a)) != EOF) {
        assert(read_char(&op) && (op == '+' || op == '*'));
        printf(" %c ", op);
        assert((fit_b = read_number(&b)) != EOF);
        puts("");
        (fit_a ? 0 : puts("first number too big"));
        (fit_b ? 0 : puts("second number too big"));
        if (fit_a && fit_b)
            r = op == '+' ? a + b : a * b;
        else
            r = (op == '*' && (a == 0 || b == 0) ? 0 : LIMIT);
        (r < LIMIT ? 0 : puts("result too big"));
    }
    return EXIT_SUCCESS;
}
