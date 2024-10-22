/* 727
 * Equation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STACK 10000
#define MAX_LINE 20

/* Whether the top of the stack must leave the stack when a character is read */
int must_leave(char stack, char read) {
    if (stack == '(') {
        return 0;
    }
    switch (read) {
        case ')': return 1;
        case '(': return 0;
        case '*':
        case '/': return stack == '*' || stack == '/';
        case '+':
        case '-': return 1;
    }
    assert(NULL);
    return 0;
}

/* Main function */
int main() {
    char operator[MAX_STACK];
    char line[MAX_LINE];
    int top, tests, first;
    assert(fgets(line, MAX_LINE, stdin) != NULL);
    for (tests = atoi(line), first = 1; tests > 0; tests--) {
        if (first) {
            assert(fgets(line, MAX_LINE, stdin) != NULL);
            assert(line[0] == '\n');
            first = 0;
        }
        else {
            printf("\n");
        }
        top = 0;
        while (fgets(line, MAX_LINE, stdin) != NULL) {
            if (line[0] == '\n') {
                break;
            }
            if (isdigit(*line)) {
                printf("%c", *line);
            }
            else {
                while (top > 0 && must_leave(operator[top - 1], *line)) {
                    printf("%c", operator[--top]);
                }
                if (*line == ')') {
                    assert(top > 0 && operator[--top] == '(');
                }
                else {
                    operator[top++] = *line;
                }
            }
        }
        while (top > 0) {
            printf("%c", operator[--top]);
        }
        printf("\n");
    }
    return 0;
}
