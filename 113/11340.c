/* 11340
 * Newspaper
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SYMBOLS 256
#define MAX_LINE 10010

#define INDEX(x) ((unsigned int) (0x0FF & (x)))

int cost[MAX_SYMBOLS];

/* Main function */
int main() {
    int tests;
    char input[MAX_LINE];
    assert(fgets(input, MAX_LINE, stdin) != NULL);
    tests = atoi(input);
    for (; tests > 0; tests--) {
        int codes, lines, payment;
        memset(cost, 0, MAX_SYMBOLS * sizeof (int));
        assert(fgets(input, MAX_LINE, stdin) != NULL);
        codes = atoi(input);
        for (; codes > 0; codes--) {
            char symbol;
            assert(fgets(input, MAX_LINE, stdin) != NULL);
            symbol = input[0];
            cost[INDEX(symbol)] = atoi(input + 2);
        }
        assert(fgets(input, MAX_LINE, stdin) != NULL);
        lines = atoi(input);
        for (payment = 0; lines > 0; lines--) {
            char *symbol;
            assert(fgets(input, MAX_LINE, stdin) != NULL);
            for (symbol = input; *symbol != 0; symbol++) {
                payment += cost[INDEX(*symbol)]; 
            }
        }
        printf("%d.%02d$\n", payment / 100, payment % 100);
    }
    return 0;
}
