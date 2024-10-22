/* 642
 * Word Amalgamation
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  8
#define MAX_WORDS   101

typedef struct {
    char *word[MAX_WORDS], key[MAX_STRING];
    int num_words;
} entry_t, *entry_p;

char word[MAX_WORDS][MAX_STRING];
entry_t entry[MAX_WORDS], *entry_ptr[MAX_WORDS];
int num_words, num_entries;

/* Compare two entries */
int compare_entries(const void *a, const void *b) {
    entry_p x = *((entry_p *) a), y = *((entry_p *) b);
    return strcmp(x->key, y->key);
}

/* Compare two strings */
int compare_words(const void *a, const void *b) {
    return strcmp(*((char **) a), *((char **) b));
}

/* Compare two characters */
int compare_chars(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}

/* Insert new word */
entry_p get_entry(char *string) {
    char key[MAX_STRING];
    int start = 0, end = num_entries;
    strcpy(key, string);
    qsort(key, strlen(key), sizeof (char), compare_chars);
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = strcmp(entry_ptr[middle]->key, key);
        if (comp == 0) {
            return entry_ptr[middle];
        }
        else if (comp < 0) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    for (end = num_entries; end > start; end--) {
        entry_ptr[end] = entry_ptr[end - 1];
    }
    strcpy(entry[num_entries].key, key);
    entry[num_entries].num_words = 0;
    entry_ptr[start] = &entry[num_entries++];
    return entry_ptr[start];
}

/* Main function */
int main() {
    entry_t key, *key_ptr;
    int i;
    num_words = 0, num_entries = 0;
    while (scanf(" %s", word[num_words]) != EOF && word[num_words][0] != 'X') {
        entry_p list = get_entry(word[num_words]);
        list->word[list->num_words++] = word[num_words];
        num_words++;
    }
    for (i = 0; i < num_entries; i++) {
        qsort(entry[i].word, entry[i].num_words, sizeof (char *), compare_words); 
    }
    key_ptr = &key;
    while (scanf(" %s", key.key) != EOF && key.key[0] != 'X') {
        entry_p *list;
        qsort(key.key, strlen(key.key), sizeof (char), compare_chars);
        list = (entry_p *) bsearch(&key_ptr, entry_ptr, num_entries, sizeof (entry_p), 
                compare_entries);
        if (list == NULL) {
            printf("NOT A VALID WORD\n");
        }
        else {
            for (i = 0; i < (*list)->num_words; i++) {
                printf("%s\n", (*list)->word[i]);
            }
        }
        printf("******\n");
    }
    return 0;
}
