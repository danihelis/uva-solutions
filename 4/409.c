/* 409
 * Excuses, Excuses!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  80
#define MAX_EXCUSES 20
#define MAX_KEYS    20

typedef char string_t[MAX_STRING];

string_t key[MAX_KEYS], excuse[MAX_EXCUSES];
int keylen[MAX_KEYS], score[MAX_EXCUSES];
int num_keys, num_excuses, max_score;

/* Convert to lower case */
void to_lower(char *s) {
    for (; *s != 0; s++) {
        *s = tolower(*s);
    }
}

/* Score an excuse */ 
void compute_score(int e) {
    string_t sentence;
    int i;
    strcpy(sentence, excuse[e]);
    to_lower(sentence);
    for (i = 0, score[e] = 0; i < num_keys; i++) {
        char *p = strstr(sentence, key[i]);
        if (p != NULL && (p == sentence || !isalpha(*(p - 1))) && !isalpha(*(p + keylen[i]))) {
            score[e]++;
        }
    }
    if (score[e] > max_score) {
        max_score = score[e];
    }
}

/* Main function */
int main() {
    int set = 0;
    while (scanf("%d %d", &num_keys, &num_excuses) != EOF) {
        int i;
        for (i = 0; i < num_keys; i++) {
            assert(scanf(" %s", key[i]) != EOF);
            to_lower(key[i]);
            keylen[i] = strlen(key[i]);
        }
        for (i = 0, max_score = 0; i < num_excuses; i++) {
            assert(scanf(" %[^\n]", excuse[i]) != EOF);
            compute_score(i);
        }
        printf("Excuse Set #%d\n", ++set);
        for (i = 0; i < num_excuses; i++) {
            if (score[i] == max_score) {
                printf("%s\n", excuse[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
