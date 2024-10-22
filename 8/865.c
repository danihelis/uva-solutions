/* 865
 * Substitution Cypher
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  70

typedef char string_t[MAX_STRING];
string_t encode, decode;

/* Decode a string of characters */
void decode_line(char *line) {
    for (; *line != '\n'; line++) {
        char *code = strchr(encode, *line);
        if (code != NULL) {
            *line = decode[code - encode];
        }
    }
}

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int num_tests;
    string_t line;
    assert(READ(line) && sscanf(line, "%d", &num_tests) != EOF);
    assert(READ(line) && line[0] == '\n');
    for (; num_tests > 0; num_tests--) {
        assert(READ(encode) && READ(decode));
        printf("%s%s", decode, encode);
        while (READ(line) && line[0] != '\n') {
            decode_line(line);
            printf("%s", line);
        }
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
