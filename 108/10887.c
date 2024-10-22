/* 10887
 * Concatenation of Languages
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  21
#define MAX_DICT    1500
#define MAX_HASH    50000017

typedef struct {
    char string[MAX_STRING];
} entry_t;

entry_t **table;
entry_t ***allocated;
char prefix[MAX_DICT][MAX_STRING];
int num_allocated;

/* Generate hash and add word to table */
void add_word(char prefix[], char suffix[]) {
    char word[MAX_STRING];
    int hash, k;
    char *c, *w;
    for (k = 0, w = word, hash = 0; k < 2; k++) {
        for (c = k == 0 ? prefix : suffix; *c != '\n'; c++, w++) {
            *w = *c;
            hash = (hash * 26 + *c - 'a') % MAX_HASH;
        }
    }
    *w = 0;
    while (table[hash] != NULL) {
        if (strcmp(table[hash]->string, word) == 0) return;
        hash = (hash + 223) % MAX_HASH;
    }
    table[hash] = (entry_t *) malloc(sizeof (entry_t));
    strcpy(table[hash]->string, word);
    allocated[num_allocated++] = &table[hash];
}

/* Free memory */
void free_table() {
    int i;
    for (i = 0; i < num_allocated; i++) {
        free(*allocated[i]);
        *allocated[i] = NULL;
    }
}

/* Main function */
int main() {
    char line[MAX_STRING];
    int test, num_tests;
    table = (entry_t **) calloc(MAX_HASH, sizeof (entry_t *));
    allocated = (entry_t ***) malloc(MAX_HASH * sizeof (entry_t **));
    assert(fgets(line, MAX_STRING, stdin) != NULL);
    assert(sscanf(line, "%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int num_prefixes, num_suffixes, i, j;
        assert(fgets(line, MAX_STRING, stdin) != NULL);
        assert(sscanf(line, "%d %d", &num_prefixes, &num_suffixes) == 2);
        for (i = 0; i < num_prefixes; i++) {
            assert(fgets(prefix[i], MAX_STRING, stdin) != NULL);
        }
        num_allocated = 0;
        for (i = 0; i < num_suffixes; i++) {
            assert(fgets(line, MAX_STRING, stdin) != NULL);
            for (j = 0; j < num_prefixes; j++) {
                add_word(prefix[j], line);
            }
        }
        printf("Case %d: %d\n", test, num_allocated);
        if (test < num_tests) free_table();
    }
    return EXIT_SUCCESS;
}
