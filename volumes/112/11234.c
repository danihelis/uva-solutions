/* 11234
 * Expressions
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT       10000

typedef struct value_s {
    struct value_s *ops[2];
    int is_operator;
    char symbol;
} value_t;

value_t values[MAX_INPUT];


/* Parse postfix notation */
value_t * parse(char *input) {
    value_t *stack[MAX_INPUT];
    int top, i;
    char *s;

    for (s = input, i = top = 0; *s != 0; s++, i++) {
        value_t *v = &values[i];
        v->symbol = *s;
        v->is_operator = isupper(*s);

        if (!v->is_operator) {
            stack[top++] = v;
        } else {
            assert(top > 1);
            v->ops[1] = stack[--top];
            v->ops[0] = stack[--top];
            stack[top++] = v;
        }
    }

    assert(top == 1);
    return stack[0];
}


/* Create queue notation */
void create_queue_notation(value_t *value, char *notation) {
    value_t *queue[MAX_INPUT];
    int front, rear;

    queue[0] = value;
    front = 0, rear = 1;

    while (front < rear) {
        value_t *v = queue[front];
        notation[front++] = v->symbol;
        if (v->is_operator) {
            queue[rear++] = v->ops[0];
            queue[rear++] = v->ops[1];
        }
    }

    /* Invert notation sequence */
    notation[rear--] = 0;
    for (front = 0; front < rear; front++, rear--) {
        char swap = notation[front];
        notation[front] = notation[rear];
        notation[rear] = swap;
    }
}


/* Main function */
int main() {
    char input[MAX_INPUT + 2], output[MAX_INPUT + 2];
    int num_tests;
    value_t *expression;

    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        assert(scanf(" %s", input) == 1);
        expression = parse(input);
        create_queue_notation(expression, output);
        printf("%s\n", output);
    }
    return EXIT_SUCCESS;
}
