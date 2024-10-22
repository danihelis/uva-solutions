/* 492
 * Pig-Latin
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORD    1000
#define VOWELS      "aeiouAEIOU"

/* Main function */
int main() {
    char input, word[MAX_WORD];
    while (scanf("%c", &input) != EOF) {
        int index = 0;
        while (isalpha(input)) {
            word[index++] = input;
            assert(scanf("%c", &input) != EOF);
        }
        if (index > 0) {
            word[index] = 0;
            if (strchr(VOWELS, word[0]) == NULL)
                printf("%s%cay", word + 1, word[0]);
            else
                printf("%say", word);
        }
        printf("%c", input);
    }
    return EXIT_SUCCESS;
}
