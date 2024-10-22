/* 12243
 * Flowers Flourish from France
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    30
#define MAX_WORDS   50
#define MAX_STRING  (MAX_SIZE * MAX_WORDS)
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)

/* Main function */
int main() {
    char input[MAX_STRING];
    while (READ(input) && input[0] != '*') {
        char tauto, letter, *i = strtok(input, " \n");
        letter = tolower(*i);
        for (tauto = 1; tauto && i != NULL; i = strtok(NULL, " \n"))
            tauto = tolower(*i) == letter;
        printf("%c\n", tauto ? 'Y' : 'N');
    }
    return EXIT_SUCCESS;
}
