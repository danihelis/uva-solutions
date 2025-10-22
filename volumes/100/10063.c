/* 10063
 * Knuth's Permutation
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING      12

/* Print all permutations of string */
void permute(char *string, int index, int size) {
    int i;
    char symbol;
    if (index >= size) {
        printf("%s\n", string);
        return;
    }

    for (i = index, symbol = string[index]; i > 0; i--) {
        string[i] = string[i - 1];
    }
    for (i = 0; i <= index; i++) {
        string[i] = symbol;
        permute(string, index + 1, size);
        if (i < index) string[i] = string[i + 1];
    }
}

/* Main function */
int main() {
    char string[MAX_STRING];
    char first = 1;

    while (scanf("%s", string) == 1) {
        first ? first = 0 : printf("\n");
        permute(string, 0, strlen(string));
    }
    return EXIT_SUCCESS;
}
