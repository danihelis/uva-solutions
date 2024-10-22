/* 622
 * Grammar Evaluation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define QUEUE_SIZE  100000

typedef enum {
    OPEN_PAR,
    CLOSE_PAR,
    SUM,
    PRODUCT
} op_t;

op_t operation[QUEUE_SIZE];
int parameter[QUEUE_SIZE];
int op_size, par_size;

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d ", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char symbol, error, last, end;
        end = error = last = op_size = par_size = 0;
        operation[op_size++] = OPEN_PAR;
        while (!error && !end && scanf("%c", &symbol) != EOF) {
            if (isdigit(symbol)) {
                if (isdigit(last)) 
                    parameter[par_size - 1] = parameter[par_size - 1] * 10 +
                            symbol - '0';
                else
                    parameter[par_size++] = symbol - '0';
            }
            else if (symbol == '+' || symbol == '*' || symbol == ')' || 
                    symbol == '\n') {
                op_t op = symbol == '+' ? SUM : symbol == '*' ? PRODUCT : 
                        CLOSE_PAR;
                error = !isdigit(last) && last != ')';
                while (!error && op_size > 0 && 
                        op <= operation[op_size - 1]) {
                    int p1, p2;
                    assert(par_size > 1);
                    p1 = parameter[par_size - 1];
                    p2 = parameter[par_size - 2];
                    parameter[--par_size - 1] = operation[--op_size] == SUM ?
                            p1 + p2 : p1 * p2;
                }
                if (op == CLOSE_PAR)
                    error = op_size == 0 || operation[--op_size] != OPEN_PAR;
                else
                    operation[op_size++] = op;
            }
            else if (symbol == '(') {
                error = isdigit(last) || last == ')';
                operation[op_size++] = OPEN_PAR;
            }
            else
                error = 1;
            last = symbol, end = symbol == '\n';
        }
        error |= op_size > 0;
        while (!end && scanf("%c", &symbol) != EOF)
            end = symbol == '\n';
        if (error)
            printf("ERROR\n");
        else {
            assert(par_size == 1);
            printf("%d\n", parameter[0]);
        }
    }
    return EXIT_SUCCESS;
}
