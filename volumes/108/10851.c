/* 10851
 * 2D Hieroglyphs decoder
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_MESSAGE     80
#define MAX_STRING      (MAX_MESSAGE + 4)
#define NUM_LINES       10

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char message[MAX_STRING], line[MAX_STRING];
        int i, j, columns;
        for (i = 0, columns = 0; i < NUM_LINES; i++) {
            assert(scanf(" %s", line) != EOF);
            if (i == 0) {
                columns = strlen(line) - 2;
                memset(message, 0, columns + 1);
            }
            else if (i < NUM_LINES - 1)
                for (j = 1; j <= columns; j++) {
                    char bit = line[j] == '/' ? 0 : 1;
                    message[j - 1] += bit << (i - 1);
                }            
        }
        printf("%s\n", message);
    }
    return EXIT_SUCCESS;
}
