/* 490
 * Rotating Sentences
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINES   105
#define MAX_STRING  (MAX_LINES + 2)
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    char text[MAX_LINES][MAX_STRING];
    int i, j, lines = 0, length[MAX_LINES], largest = 0;
    while (fgets(text[lines], MAX_STRING, stdin) != NULL) {
        length[lines] = strlen(text[lines]) - 1;
        largest = MAX(largest, length[lines]);
        lines++;
    }
    for (i = 0; i < largest; i++) {
        for (j = lines - 1; j >= 0; j--) {
            printf("%c", (i < length[j] ? text[j][i] : ' '));
        }
        printf("\n");
    }

    return 0;
}
