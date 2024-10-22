/* 10896
 * Known Plaintext Attack
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      80
#define NUM_LETTERS     26

char used[NUM_LETTERS];
char keys[NUM_LETTERS + 1];
int num_keys;

/* Compare two chars */
int compare(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}

/* Decrypt and insert key */
void decypt_and_insert(char *word, char *crypt) {
    char *w, *c, eq;
    int key = (crypt[0] - word[0] + NUM_LETTERS) % NUM_LETTERS;
    for (w = word + 1, c = crypt + 1, eq = !used[key]; eq && *c != 0; w++, c++) {
        eq = (*w - 'a' + key) % NUM_LETTERS == (*c - 'a');
    }
    if (eq) {
        keys[num_keys] = key + 'a', used[key] = 1;
        num_keys++;
    }
}

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char line[MAX_STRING], word[MAX_STRING];
    int num_tests, length;
    assert(READ(line));
    for (num_tests = atoi(line); num_tests > 0; num_tests--) {
        char *token;
        assert(READ(line) && READ(word));
        token = strchr(word, '\n');
        *token = 0, length = token - word;
        num_keys = 0;
        memset(used, 0, NUM_LETTERS);
        token = strtok(line, " \n");
        while (token != NULL) {
            if (strlen(token) == length) {
                decypt_and_insert(word, token);
            }
            token = strtok(NULL, " \n");
        }
        qsort(keys, num_keys, sizeof (char), compare);
        keys[num_keys] = 0;
        printf("%s\n", keys);
    }
    return 0;
}
