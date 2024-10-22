/* 11291
 * Smeech
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Parse expression */
int parse(double *value, char *last) {
    char symbol;
    assert(scanf(" %c", &symbol) == 1);
    if (symbol != '(') {
        int number = 0, signal = 1;
        if (symbol == '-')
            signal = -1, symbol = getchar();
        do {
            number = number * 10 + symbol - '0';
            symbol = getchar();
        } while (isdigit(symbol));
        *last = symbol;
        *value = number * signal;
    }
    else {
        double prob, e1, e2;
        if (scanf("%lf", &prob) != 1)
            return 0;
        parse(&e1, last);
        parse(&e2, last);
        while (*last != ')')
            *last = getchar();
        *value = prob * (e1 + e2) + (1 - prob) * (e1 - e2);
        *last = 0;
    }
    return 1;
}

/* Main function */
int main() {
    char last;
    double value;
    while (parse(&value, &last))
        printf("%.2f\n", value);
    return EXIT_SUCCESS;
}
