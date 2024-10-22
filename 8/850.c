/*
 * 850
 * Crypt Kicker II
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_LETTERS 26
#define STRING_SIZE 85
#define MAX_LINES 100

typedef char string_t[STRING_SIZE];
string_t line[MAX_LINES];
int num_lines;

string_t key = "the quick brown fox jumps over the lazy dog";
char crypt[NUM_LETTERS];

#define CHAR_AT(i, c) (line[(i)][(c)] - 'a')

/* Find encryption key */
#define KEY_SIZE 43 /* strlen(key) */
int find_encryption_key() {
    int i, pos;
    for (i = 0; i < num_lines; i++) {
        pos = strlen(line[i]) - 1;
        if (pos == KEY_SIZE) {
            pos = 0;
            memset(crypt, 0, NUM_LETTERS);
            while (pos < KEY_SIZE) {
                if (line[i][pos] == ' ') {
                    if (key[pos] != ' ') {
                        break;
                    }
                }
                else {
                    if (crypt[CHAR_AT(i, pos)] == 0) {
                        crypt[CHAR_AT(i, pos)] = key[pos];
                    }
                    else if (crypt[CHAR_AT(i, pos)] != key[pos]) {
                        break;
                    }
                }
                pos++;
            }
            if (pos >= KEY_SIZE) {
                return 1;
            }
        }
    }
    return 0;
}


/* Decrypt lines once encryption is found */
void decrypt_lines() {
    int i, pos;
    for (i = 0; i < num_lines; i++) {
        for (pos = 0; line[i][pos] != '\n'; pos++) {
            printf("%c", (line[i][pos] == ' ' ? ' ' : crypt[CHAR_AT(i, pos)]));
        }
        printf("\n");
    }
}


/* Main function */
int main() {
    int num_tests, test;

    assert(fgets(line[0], STRING_SIZE, stdin) != NULL);
    num_tests = atoi(line[0]);

    for (test = 0; test < num_tests; test++) {
        (test == 0 ? assert(fgets(line[0], STRING_SIZE, stdin) != NULL) : (void) printf("\n"));
    
        num_lines = 0;
        while (fgets(line[num_lines], STRING_SIZE, stdin) != NULL) {
            if (line[num_lines][0] == '\n') {
                break;
            }
            num_lines++;
        }

        if (!find_encryption_key()) {
            printf("No solution.\n");
        }
        else {
            decrypt_lines();
        }
    }

    return 0;
}
