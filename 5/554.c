/* 554
 * Caesar Cypher
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS       101
#define MAX_WORD_SIZE   25
#define MAX_MESSAGE     255
#define MAX_K           27
#define MAX_COLUMNS     60

char dict[MAX_WORDS][MAX_WORD_SIZE], *p_dict[MAX_WORDS];
int size;

/* Compare */
int compare(const void *a, const void *b) {
    return strcmp(* (char **) a, * (char **) b);
}

/* Decode using K */
void decode(char *input, char *output, int k) {
    char *i, *o;
    for (i = input, o = output; *i != 0; i++, o++) {
        int code = ((*i == ' ' ? 0 : *i - 'A' + 1) + k) % MAX_K;
        *o = (code == 0 ? ' ' : 'A' + code - 1);
    }
    *o = 0;
}

/* Main function */
int main() {
    char input[MAX_WORD_SIZE], cypher[MAX_MESSAGE];
    size = 0;
    while (scanf(" %s", input) != EOF && input[0] != '#') {
        strcpy(dict[size], input);
        p_dict[size] = dict[size];
        size++;
    }
    qsort(p_dict, size, sizeof (char *), compare);
    while (scanf(" %[^\n]", cypher) != EOF) {
        int k, matches, best_matches, best_k;
        char message[MAX_MESSAGE], *token;
        for (k = 0, best_matches = best_k = -1; k < MAX_K; k++) {
            decode(cypher, message, k);
            for (matches = 0, token = strtok(message, " "); token != NULL; 
                    token = strtok(NULL, " "))
                if (bsearch(&token, p_dict, size, sizeof (char *), compare))
                    matches++;
            if (matches > best_matches)
                best_k = k, best_matches = matches;
        }
        decode(cypher, message, best_k);
        for (token = strtok(message, " "), k = 0; token != NULL;
                token = strtok(NULL, " ")) {
            int length = strlen(token);
            if (k + length > MAX_COLUMNS) {
                printf("\n");
                k = 0;
            }
            printf("%s%s", k > 0 ? " " : "", token);
            k = length + k + (k > 0 ? 1 : 0);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
