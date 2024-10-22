/*
 * 848
 * Fmt
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE 72
#define INPUT_SIZE 500

char buffer[INPUT_SIZE * 2];
char input[INPUT_SIZE];


/* Reduce buffer to less than maximum allowed by line */
void reduce_buffer() {
    char *line, *pos;
    line = buffer;
    while (strlen(line) > MAX_LINE) {
        /* Find the nearest left space from mark */
        pos = line + MAX_LINE;
        while (pos != line && *pos != ' ') {
            pos--;
        }
        while (pos != line && *pos == ' ') {
            pos--;
        }
        if (pos != line) {
            pos++;
        }
        /* In case there isn't such space, find nearest right */
        if (pos == line) {
            pos = strchr(line, ' ');
            if (pos == NULL) {
                printf("%s\n", line);
                buffer[0] = '\0';
                return;
            }
        }
        *pos = '\0';
        printf("%s\n", line);
        /* Erase all following spaces */
        do {
            pos++;
        }
        while (*pos == ' ');
        line = pos;
    }
    if (line != buffer) {
        for (pos = buffer; *line != '\0'; pos++, line++) {
            *pos = *line;
        }
        *pos = '\0';
    }
}


/* Empty buffer */
void empty_buffer() {
    reduce_buffer();
    if (buffer[0] != '\0') {
        printf("%s\n", buffer);
        buffer[0] = '\0';
    }
}


/* Treat new line, either printing out buffer or joining this line to buffer */
void treat_new_line() {
    char *end = strchr(input, '\n');
    *end = '\0';
    if (input[0] == '\0' || input[0] == ' ') {
        empty_buffer();
        strcpy(buffer, input);
        if (input[0] == '\0') {
            printf("\n");
        }
    }
    else {
        if (buffer[0] != '\0') {
            strcat(buffer, " ");
        }
        strcat(buffer, input);
        reduce_buffer();
    }
}


/* Main function */
int main() {
    buffer[0] = '\0';
    while (fgets(input, INPUT_SIZE, stdin) != NULL) {
        /* printf(">>>%s", input); */
        treat_new_line();
    }
    empty_buffer();
    return 0;
}
