/* 526
 * String Distance and Transform Process
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE    100

typedef enum {
    NONE,
    INSERT,
    DELETE,
    REPLACE
} op_t;

typedef struct {
    int cost, index;
    char symbol;
    op_t operation;
} cell_t;

/* Determine smallest transformation */
void transformation(char *input, char *output, cell_t *stack, int *len) {
    cell_t matrix[MAX_LINE][MAX_LINE];
    int i, j, in_len, out_len;
    in_len = strlen(input) - 1, out_len = strlen(output) - 1;
    for (i = 0; i <= in_len; i++) {
        cell_t *c = &matrix[i][0];
        c->cost = i, c->index = 1, c->operation = i == 0 ? NONE : DELETE;
    }
    for (j = 1; j <= out_len; j++) {
        cell_t *c = &matrix[0][j];
        c->cost = j, c->index = j, c->operation = INSERT, 
                c->symbol = output[j - 1];
        for (i = 1; i <= in_len; i++) {
            cell_t *c = &matrix[i][j];
            c->cost = matrix[i - 1][j - 1].cost, c->operation = NONE;
            c->index = j, c->symbol = output[j - 1];
            if (input[i - 1] != output[j - 1])
                c->cost += 1, c->operation = REPLACE;
            if (c->cost > matrix[i][j - 1].cost + 1)
                c->cost = matrix[i][j - 1].cost + 1, c->operation = INSERT;
            if (c->cost > matrix[i - 1][j].cost + 1)
                c->cost = matrix[i - 1][j].cost + 1, c->operation = DELETE,
                        c->index++;
        }
    }
    for (i = in_len, j = out_len, *len = 0; i > 0 || j > 0; ) {
        cell_t *c = &matrix[i][j];
        if (c->operation != NONE)
            stack[(*len)++] = *c;
        i -= c->operation != INSERT ? 1 : 0;
        j -= c->operation != DELETE ? 1 : 0;
    }
}

/* Print operation */
void print_operations(cell_t *stack, int top) {
    int count;
    printf("%d\n", top);
    for (count = 1; top > 0; top--, count++) {
        cell_t *c = &stack[top - 1];
        printf("%d %s %d", count, c->operation == INSERT ? "Insert" :
                c->operation == DELETE ? "Delete" : "Replace", c->index);
        if (c->operation != DELETE)
            printf(",%c", c->symbol);
        printf("\n");
    }
}

/* Main function */
#define READ(x)     (fgets(x, MAX_LINE, stdin) != NULL)
int main() {
    char input[MAX_LINE], output[MAX_LINE];
    cell_t stack[MAX_LINE];
    int first = 1, top;
    while (READ(input) && READ(output)) {
        (first ? (first = 0) : printf("\n"));
        transformation(input, output, stack, &top);
        print_operations(stack, top);
    }
    return EXIT_SUCCESS;
}
