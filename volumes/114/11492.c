/* 11492
 * Babel
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH 60
#define MAX_WORDS 2000
#define MAX_LANGUAGES (2 * MAX_WORDS)
#define INFINITE (MAX_WORDS * MAX_LENGTH + 1)

typedef char string_t[MAX_LENGTH];

struct language_s;

typedef struct {
    struct language_s *pair[2];
    char first;
    int size;
    int source, cost;
} word_t, *word_p;

word_t word[MAX_WORDS];
int num_words;

typedef struct language_s {
    word_p *word;
    string_t name;
    int num_words, max_words;
} language_t, *language_p;

language_t language[MAX_LANGUAGES];
language_p lang_index[MAX_LANGUAGES];
int num_languages;

/* Find language or add a new one */
language_p find_language(string_t *name, char must_add) {
    int start = 0, end = num_languages;
    while (start < end) {
        int middle, comp;
        middle = (start + end) / 2;
        comp = strcmp(lang_index[middle]->name, *name);
        if (comp == 0) {
            return lang_index[middle];
        }
        else if (comp < 0) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    if (!must_add) {
        return NULL;
    }
    for (end = num_languages; end > start; end--) {
        lang_index[end] = lang_index[end - 1];
    }
    lang_index[start] = &language[num_languages++];
    strcpy(lang_index[start]->name, *name);
    lang_index[start]->num_words = 0, lang_index[start]->max_words = 0;
    lang_index[start]->word = NULL;
    return lang_index[start];
}

/* Add new word */
void add_word(string_t *word_name, string_t lang_name[]) {
    word_p new_word = &word[num_words++];
    int i;
    for (i = 0; i < 2; i++) {
        language_p lang = find_language(&lang_name[i], 1);
        if (lang->num_words >= lang->max_words) {
            lang->max_words += 2;
            lang->word = (word_p *) realloc(lang->word, lang->max_words * sizeof (word_p));
        }
        lang->word[lang->num_words++] = new_word;
        new_word->pair[i] = lang;
    }
    new_word->first = (*word_name)[0];
    new_word->size = strlen(*word_name);
}

/* Find minimum distance from one language to another */
int minimum_distance(string_t lang_name[]) {
    word_p last_word, queue[MAX_WORDS];
    int i, size, found;
    language_p lang_from = find_language(&lang_name[0], 0), 
               lang_to = find_language(&lang_name[1], 0);
    if (lang_from == NULL || lang_to == NULL) {
        return INFINITE;
    }
    for (i = 0; i < num_words; i++) {
        word[i].cost = INFINITE;
    }
    size = 0, found = 0;
    do {
        int minimum = 0;
        language_p cur_lang = lang_from;
        last_word = NULL;
        for (i = 0; i < size; i++) {
            if (last_word == NULL || last_word->cost > queue[i]->cost) {
                minimum = i;
                last_word = queue[i];
            }
        }
        if (last_word != NULL) {
            queue[minimum] = queue[--size];                        
            cur_lang = last_word->pair[1 - last_word->source];
        }
        if (cur_lang == lang_to) {
            found = 1;
            break;
        }
        for (i = 0; i < cur_lang->num_words; i++) {
            word_p next_word = cur_lang->word[i];
            if (last_word != NULL && next_word->first == last_word->first) {
                continue;
            }
            if (next_word->cost == INFINITE) {
                queue[size++] = next_word;
            }
            if (next_word->cost > (last_word == NULL ? 0 : last_word->cost) + next_word->size) {
                next_word->cost = (last_word == NULL ? 0 : last_word->cost) + next_word->size;
                next_word->source = (next_word->pair[0] == cur_lang ? 0 : 1);
            }
        }
    } while (size > 0);
    if (!found) {
        return INFINITE;
    }
    return (last_word != NULL ? last_word->cost : 0);
}

/* Deallocate all memory */
void free_languages() {
    int i;
    for (i = 0; i < num_languages; i++) {
        assert(language[i].word != NULL);
        free(language[i].word);
    }
}

/* Main function */
int main() {
    int num_entries;
    while (scanf("%d", &num_entries) != EOF && num_entries > 0) {
        int i, cost;
        string_t query[2];
        assert(scanf(" %s %s", query[0], query[1]) != EOF);
        num_languages = 0, num_words = 0;
        for (i = 0; i < num_entries; i++) {
            string_t input[3];
            assert(scanf(" %s %s %s", input[0], input[1], input[2]) != EOF);
            add_word(&input[2], input);
        }
        cost = minimum_distance(query);
        if (cost == INFINITE) {
            printf("impossivel\n");
        }
        else {
            printf("%d\n", cost);
        }
        free_languages();
    }
    return 0;
}
