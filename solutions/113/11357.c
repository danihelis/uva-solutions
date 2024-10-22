/* 11357
 * Ensuring Truth
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VARS    26

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d ", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char symbol, var[MAX_VARS];
        int formula, clause, value, index;
        formula = 0;
        while (scanf("%c", &symbol) != EOF && symbol != '\n') {
            if (symbol == '|')
                assert(scanf("%c", &symbol) != EOF && symbol == '(');
            memset(var, -1, MAX_VARS);
            clause = 1;
            do {
                if (clause) {
                    assert(scanf("%c", &symbol) != EOF);
                    value = 1;
                    if (symbol == '~') {
                        value = 0;
                        assert(scanf("%c", &symbol) != EOF);
                    }
                    assert(islower(symbol));
                    index = symbol - 'a';
                    if (var[index] == -1)
                        var[index] = value;
                    else
                        clause = var[index] == value;
                }
            } while (scanf("%c", &symbol) != EOF && symbol != ')');
            formula |= clause;
        }
        printf("%s\n", formula ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
