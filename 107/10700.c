/* 10700
 * Camel trading
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           12
#define MAX_STRING      300

/* Interpret an expression */
void interpret(char *expression, long *max, long *min) {
    long max_stack[MAX_N], min_stack[MAX_N];
    int max_t, min_t;    
    char *s;
    max_stack[0] = min_stack[0] = strtol(expression, &s, 10);
    max_t = min_t = 1;
    while (s != NULL && *s != 0) {
        char op = *s;
        long next = strtol(s + 1, &s, 10);
        if (op == '+') {
            max_stack[max_t - 1] += next;
            min_stack[min_t++] = next;
        }
        else {
            min_stack[min_t - 1] *= next;
            max_stack[max_t++] = next;
        }
    }
    for (--min_t; min_t > 0; min_t--)
        min_stack[min_t - 1] += min_stack[min_t];
    for (--max_t; max_t > 0; max_t--)
        max_stack[max_t - 1] *= max_stack[max_t];
    *max = max_stack[0], *min = min_stack[0];
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        char input[MAX_STRING];
        long max, min;
        assert(scanf(" %s", input) == 1);
        interpret(input, &max, &min);
        printf("The maximum and minimum are %ld and %ld.\n", max, min);
    }
    return EXIT_SUCCESS;
}
