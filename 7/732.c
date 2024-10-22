/* 732
 * Anagrams by Stack
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1000
#define MAX_STACK   (MAX_STRING * 2)
#define END         '\n'
#define READ(line)  (fgets(line, MAX_STRING, stdin) != NULL)

char source[MAX_STRING], target[MAX_STRING], stack[MAX_STRING];
char process[MAX_STACK];

/* Process stack to obtain target from source */
void process_stack(char *s, char *t, int size, int i) {
    if (*s == END && *t == END && size == 0) {
        int j;
        for (j = 0; j < i; j++) {
            printf("%c%s", process[j], j < i - 1 ? " " : "\n");
        }
        return;
    }
    if (*s != END && *t != END) {
        /* Push in the stack */
        char back = stack[size];
        stack[size] = *s;
        process[i] = 'i';
        process_stack(s + 1, t, size + 1, i + 1);
        stack[size] = back;
    }
    if (size > 0 && stack[size - 1] == *t) {
        /* Pop from stack */
        process[i] = 'o';
        process_stack(s, t + 1, size - 1, i + 1);
    }
}

/* Main function */
int main() {
    while (READ(source) && READ(target)) {
        printf("[\n");
        process_stack(source, target, 0, 0);
        printf("]\n");
    }
    return 0;
}
