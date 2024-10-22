/* 10293
 * Word Length and Frequency
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100
#define MAX_WORD    40

int count[MAX_WORD];

/* Main function */
int main() {
    char line[MAX_STRING];
    while (fgets(line, MAX_STRING, stdin) != NULL) {
        int i, word_size = 0;
        char *symbol, last;
        memset(count, 0, MAX_WORD * sizeof (int));

        if (line[0] == '\n') {
            break; /* The input is really malformed! :( */
        }

        while (line[0] != '#') {
            for (symbol = line, last = 0; *symbol != '\n'; symbol++) {
                if (isalpha(*symbol)) {
                    word_size++;
                }
                else if (*symbol != '\'' && *symbol != '-' && word_size > 0) {
                    count[word_size]++;
                    word_size = 0;
                }
                last = *symbol;
            }
            assert(fgets(line, MAX_STRING, stdin) != NULL);
            if (last != '-' && word_size > 0) {
                count[word_size]++;
                word_size = 0;
            }
        }
        for (i = 1; i < MAX_WORD; i++) {
            if (count[i] != 0) {
                printf("%d %d\n", i, count[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
