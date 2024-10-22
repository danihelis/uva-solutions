/* 483
 * Word Scramble
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORD 10000

/* Main function */
int main() {
    char word[MAX_WORD];
    int size = 0;
    char letter;
    while (scanf("%c", &letter) != EOF) {
        if (isgraph(letter)) {
            word[size++] = letter;
        }
        else {
            while (size > 0) {
                printf("%c", word[--size]);
            }
            printf("%c", letter);
        }
    }
    while (size > 0) {
        printf("%c", word[--size]);
    }
    return 0;
}
