/**
 * 112
 * Tree Summing
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define MAX_STACK 1024
#define MAX_LINE 1024

#define SPACE(n) \
    do { \
        int space_i_; \
        for (space_i_ = 0; space_i_ < (n); space_i_++) { \
            printf("  "); \
        } \
    } while (0)

typedef enum {
    BOTH_UNEXPLORED,
    LEFT_EXPLORED,
    LEFT_VOID,
    BOTH_EXPLORED,
    VOID
} node_status;

typedef struct {
    node_status status;
    int value, count;
} stack_t;

stack_t stack[MAX_STACK];
int top;

char line[MAX_LINE];
char *line_p;

int aim_number, found;


/* Get another line. Return 0 if none remains. */
int get_line() {
    line_p = fgets(line, MAX_LINE, stdin);
    return line_p != NULL;
}


/* Read spaces */
void read_space() {
    int stop = 0;
    while (!stop) {
        while (*line_p == ' ' || *line_p == '\t') {
            line_p++;
        }
        if (*line_p == '\n' || *line_p == '\r' || *line_p == '\0') {
            assert(get_line());
        }
        else {
            stop = 1;
        }
    }
}


/* Read a number */
void read_number(int *n) {
    int signal = 1;
    read_space();
    if (*line_p == '-') {
        signal = -1;
        line_p++;
    }
    *n = 0;
    while (*line_p >= '0' && *line_p <= '9') {
        *n *= 10;
        *n += *line_p - '0';
        line_p++;
    }
    *n *= signal;
}


/* Read a tree */
void read_tree() {
    top = 0;
    found = 0;

    do {
        read_space();

        /* End a tree */
        if (*line_p == ')') {
            line_p++;
            top--;
            if (top > 0) {
                if (stack[top - 1].status == BOTH_UNEXPLORED) {
                    stack[top - 1].status = (stack[top].status == VOID ? LEFT_VOID : LEFT_EXPLORED);
                }
                else if (stack[top - 1].status != BOTH_EXPLORED) {
                    if (stack[top - 1].status == LEFT_VOID && stack[top].status == VOID) {
                        /* SPACE(top); printf(": Leaf has count: %d\n", stack[top - 1].count); */
                        found += (stack[top - 1].count == aim_number ? 1 : 0);
                    }
                    stack[top - 1].status = BOTH_EXPLORED;
                }
            }
        }
        /* Start a tree */
        else if (*line_p == '(') {
            line_p++;
            /* SPACE(top); printf(": Start of a tree\n"); */
            stack[top].count = (top == 0 ? 0 : stack[top - 1].count);
            stack[top].status = BOTH_UNEXPLORED;
            top++;
            read_space();

            /* An empty tree */
            if (*line_p == ')') {
                stack[top - 1].status = VOID;
            }
            /* A full tree */
            else {
                read_number(&stack[top - 1].value);
                stack[top - 1].count += stack[top - 1].value;
                /*
                SPACE(top - 1); printf(": New node has value: %d and count: %d\n", 
                        stack[top - 1].value, stack[top - 1].count);
                */
            }
        }
    }
    while (top > 0);    
}


/* Main */
int main() {
    while (get_line()) {
        read_number(&aim_number);
        /* printf("Aim value is: %d\n", aim_number); */
        read_tree();
        if (found) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }
    return 0;
}
