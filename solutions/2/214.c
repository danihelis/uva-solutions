/* 214
 * Code Generation
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    char reg, operand, stack, symbol, first = 1;
    reg = operand = stack = 0;
    while (scanf("%c", &symbol) != EOF) {
        if (symbol == '\n') {
            if (operand != 0) {
                assert(reg == 0);
                (first ? (first = 0) : printf("\n"));
                printf("L %c\n", operand);
            }
            reg = operand = stack = 0;
            continue;
        }
        if (isalpha(symbol) || symbol == '@') {
            if (operand != 0) {
                if (reg != 0) {
                    printf("ST $%d\n", stack++);
                }
                else {
                    (first ? (first = 0) : printf("\n"));
                }
                printf("L %c\n", operand);
                reg = operand; \
            }
            if (symbol == '@') {
                printf("N\n");
                operand = 0;
            }
            else {
                operand = symbol;
            }
        }
        else if (operand != 0) {
            printf("%c %c\n", symbol == '+' ? 'A' : 
                              symbol == '-' ? 'S' :
                              symbol == '*' ? 'M' : 'D', operand);
            operand = 0;
        }
        else {
            assert(stack > 0);
            switch (symbol) {
                case '+':
                case '*':
                    printf("%c $%d\n", symbol == '+' ? 'A' : 'M', --stack);
                    break;
                case '-':
                    printf("N\nA $%d\n", --stack);
                    break;
                case '/':
                    printf("ST $%d\nL $%d\nD $%d\n", stack, stack - 1, 
                            stack);
                    stack--;
                    break;
            }
        }
    }
    return 0;
}
