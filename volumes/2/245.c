/* 245
 * Uncompress
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS   1000000
#define MAX_STRING  52
#define READ(x)     (assert(scanf("%c", x) == 1))

char *dict[MAX_WORDS];
int num_words;

/* Main function */
int main() {
    char symbol, *w, word[MAX_STRING];
    int index, length;
    num_words = 0;
    READ(&symbol);
    while (1) {
        if (isalpha(symbol)) {
            w = word, length = 0;            
            do {
                *w = symbol;
                w++, length++;
                READ(&symbol);
            } while (isalpha(symbol));
            *w = 0;
            dict[num_words] = (char *) malloc(length + 1);
            strcpy(dict[num_words++], word);
            printf("%s", word);
        } else if (isdigit(symbol)) {
            index = 0;
            do {
                index = (index * 10) + symbol - '0';
                READ(&symbol);
            } while (isdigit(symbol));
            if (index == 0) break;
            assert(index <= num_words);
            index = num_words - index;
            printf("%s", dict[index]);
            if (index < num_words - 1) {
                w = dict[index];
                for (; index < num_words - 1; index++) {
                    dict[index] = dict[index + 1];
                }
                dict[index] = w;
            }
        } else {
            printf("%c", symbol);
            READ(&symbol);
        }
    }
    return EXIT_SUCCESS;
}
