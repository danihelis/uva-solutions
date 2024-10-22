/* 12195
 * Jingle Composing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      210
#define CORRECT_SUM     64
#define STOP            "/"

char symbols[] = "WHQESTX";
int values[] = {64, 32, 16, 8, 4, 2, 1};

/* Main function */
int main() {
    char input[MAX_STRING];
    while (scanf(" %s", input) == 1 && input[0] != '*') {
        char *i;
        int count, sum;
        for (i = strtok(input, STOP), count = 0; i != NULL; 
                i = strtok(NULL, STOP)) {
            for (sum = 0; *i != 0; i++) {
                char *s = strchr(symbols, *i);
                sum += values[s - symbols];
            }
            count += sum == CORRECT_SUM ? 1 : 0;
        }
        printf("%d\n", count);
    }
    return EXIT_SUCCESS;
}
