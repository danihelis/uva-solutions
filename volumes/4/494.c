/* 494
 * Kindergarten Counting Game
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int words = 0, last_alpha = 0;
    char letter;
    while (scanf("%c", &letter) != EOF) {
        int is_alpha = isalpha(letter);
        if (letter == '\n') {
            printf("%d\n", words);
            words = 0;
        }
        else if (is_alpha && !last_alpha) {
            words++;
        }
        last_alpha = is_alpha;
    }
    return 0;
}
