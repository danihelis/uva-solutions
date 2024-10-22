/* 10683
 * The decadary watch
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CENTS_IN_SECONDS 100
#define CENTS_IN_MINUTES (60 * CENTS_IN_SECONDS)
#define CENTS_IN_HOURS   (60 * CENTS_IN_MINUTES)
#define CENTS_IN_DAYS    (24 * CENTS_IN_HOURS)
#define MAX_OUTPUT 20
#define NUM_DIGITS 8
#define TO_DECIMAL(x) ((x) - '0')

long multiple[NUM_DIGITS] = {
    10 * CENTS_IN_HOURS, CENTS_IN_HOURS, 10 * CENTS_IN_MINUTES, CENTS_IN_MINUTES,
    10 * CENTS_IN_SECONDS, CENTS_IN_SECONDS, 10, 1};

/* Main function */
int main() {
    char output[MAX_OUTPUT];
    char symbol;
    int i;
    while (scanf(" %c", &symbol) != EOF) {
        long cents = TO_DECIMAL(symbol) * multiple[0];
        for (i = 1; i < NUM_DIGITS; i++) {
            assert(scanf("%c", &symbol) != EOF);
            cents += TO_DECIMAL(symbol) * multiple[i];
        }
        sprintf(output, "%016.8f", cents * 10000000.0 / (double) CENTS_IN_DAYS);
        output[7] = 0;
        printf("%s\n", output);
    }
    return 0;
}
