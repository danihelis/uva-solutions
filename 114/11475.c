/* 11475
 * Extend to Palindrome
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    100002
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    char input[MAX_SIZE];
    while (scanf(" %s", input) != EOF) {
        char *start, *end, *i, *j;
        start = input;
        end = input + strlen(input) - 1;
        while (start < end) {
            for (i = start, j = end; i < j && *i == *j; i++, j--)
                ;
            if (i >= j)
                break;
            start++; /* = MAX(i, start + 1);*/
        }
        printf("%s", input);
        for (--start; start >= input; start--)
            printf("%c", *start);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
