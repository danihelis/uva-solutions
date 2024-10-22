/* 10815
 * Andy's First Dictionary
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS   50000
#define MAX_STRING  250

typedef char string_t[MAX_STRING];
typedef string_t *string_p;

string_t word[MAX_WORDS];
char *dict[MAX_WORDS];
int num_words;

/* Insert a new word, if not existent */
void insert(char *w) {
    int start, end, middle, comp;
    start = 0, end = num_words;
    while (start < end) {
        middle = (start + end) / 2;
        comp = strcmp(w, dict[middle]);
        if (comp == 0) {
            return;
        }
        else if (comp < 0) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }
    for (end = num_words; end > start; end--) {
        dict[end] = dict[end - 1];
    }
    strcpy(word[num_words], w);
    dict[start] = word[num_words];
    num_words++;
}

/* Main function */
int main() {
    string_t line, cur_word;
    int i;
    num_words = 0;
    while (fgets(line, MAX_STRING, stdin) != NULL) {
        char *w, *c;
        for (w = line, c = cur_word; *w != 0; w++) {
            if (isalpha(*w)) {
                *c = tolower(*w);
                c++;
            }
            else if (c > cur_word) {
                *c = 0;
                insert(cur_word);
                c = cur_word;
            }
        }
    }
    for (i = 0; i < num_words; i++) {
        printf("%s\n", dict[i]);
    }
    return 0;
}
