/* 673
 * Parentheses Balance
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH 200

/* Main function */
int main() {
    char stack[MAX_LENGTH];
    char line[MAX_LENGTH];
    int top, tests;
    assert(fgets(line, MAX_LENGTH, stdin) != NULL);
    for (tests = atoi(line); tests > 0; tests--) {
        char *symbol;
        int correct;
        assert(fgets(line, MAX_LENGTH, stdin) != NULL);
        for (top = 0, correct = 1, symbol = line; correct && *symbol != '\n'; symbol++) {
            if (*symbol == '(' || *symbol == '[') {
                stack[top++] = (*symbol == '(' ? ')' : ']');
            }
            else {
                correct = (top > 0 && *symbol == stack[--top]);
            }
        }
        correct = (correct && top == 0);
        printf("%s\n", correct ? "Yes" : "No");
    }

    return 0;
}
