/* 11220
 * Decoding the message.
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  35
#define MAX_WORDS   30
#define MAX_LINE    (MAX_STRING * MAX_WORDS)

#define READ(x)     (fgets(x, MAX_LINE, stdin) != NULL)

/* Main function */
int main() {
    int test, num_tests;
    char line[MAX_LINE];
    assert(READ(line));
    num_tests = atoi(line);
    assert(READ(line) && line[0] == '\n');
    for (test = 1; test <= num_tests; test++) {
        printf("%sCase #%d:\n", test > 1 ? "\n" : "", test);
        while (!feof(stdin)) {
            int i;
            char *s;
            if (!READ(line) || line[0] == '\n')
                break;
            for (i = 0, s = strtok(line, " \n"); s != NULL; 
                    s = strtok(NULL, " \n"))
                if (i < strlen(s))
                    putchar(s[i++]);
            puts("");
        }
    }
    return EXIT_SUCCESS;
}
