/*
 * 10188
 * Automated Judge Script
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINES 100
#define STRING_SIZE 125
#define STRING_NUMBER_SIZE (MAX_LINES * STRING_SIZE)
#define NUMBERS "0123456789"

typedef enum {
    SOLUTION = 0,
    ANSWER = 1
} kind_t;

typedef enum {
    ACCEPTED,
    PRESENTATION_ERROR,
    WRONG
} veredict_t;

char text[2][MAX_LINES][STRING_SIZE];
char numeric[2][STRING_NUMBER_SIZE];
int text_size[2], numeric_size[2];


/* Read entry and fetch numeric data */
void read_input(int size, kind_t k) {
    int i;
    char *c;
    text_size[k] = size;
    numeric_size[k] = 0;

    for (i = 0; i < text_size[k]; i++) {
        assert(fgets(text[k][i], STRING_SIZE, stdin) != NULL);
        c = strpbrk(text[k][i], NUMBERS);
        while (c != NULL) {
            numeric[k][numeric_size[k]] = *c;
            numeric_size[k]++;
            c = strpbrk(c + 1, NUMBERS);
        }
    }
    numeric[k][numeric_size[k]] = '\0';
}


/* Judge the answer, comparing with the solution */
veredict_t judge_answer() {
    int i;
    if ((numeric_size[SOLUTION] != numeric_size[ANSWER]) || strcmp(numeric[SOLUTION], numeric[ANSWER]) != 0) {
        return WRONG;
    }
    if (text_size[SOLUTION] != text_size[ANSWER]) {
        return PRESENTATION_ERROR;
    }
    for (i = 0; i < text_size[SOLUTION]; i++) {
        if (strcmp(text[SOLUTION][i], text[ANSWER][i]) != 0) {
            return PRESENTATION_ERROR;
        }
    }
    return ACCEPTED;
}


/* Main function */
int main() {
    char input[STRING_SIZE];
    int size, run = 1;

    while (fgets(input, STRING_SIZE, stdin) != NULL) {
        size = atoi(input);
        if (size == 0) {
            break;
        }
        read_input(size, SOLUTION);
        assert(fgets(input, STRING_SIZE, stdin) != NULL);
        size = atoi(input);
        read_input(size, ANSWER);

        printf("Run #%d: ", run++);
        switch (judge_answer()) {
            case ACCEPTED: printf("Accepted\n"); break;
            case PRESENTATION_ERROR: printf("Presentation Error\n"); break;
            case WRONG: printf("Wrong Answer\n");
        }
    }
    return 0;
}
