/* 271
 * Simply Syntax
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  300

/* Main function */
int main() {
    int stack, correct;
    char string[MAX_STRING], *p;
    while (fgets(string, MAX_STRING, stdin) != NULL) {
        for (p = string, stack = 1, correct = 1; stack > 0 && correct && *p != '\n'; p++) {
            stack += (*p == 'N' ? 0 : isupper(*p) ? 1 : -1);
        }
        correct &= stack == 0 && *p == '\n';
        printf("%s\n", correct ? "YES" : "NO");
    }
    return 0;
}
