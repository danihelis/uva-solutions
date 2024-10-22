/**
 * 123
 * Searching Quickly
 * by Daniel Donadon
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS_IN_TITLE 15
#define MAX_TITLES 200
#define MAX_IGNORE_TERMS 50
#define MAX_TERMS (MAX_WORDS_IN_TITLE * MAX_TITLES + MAX_IGNORE_TERMS)
#define MAX_WORD_SIZE 20
#define MAX_LINE_SIZE 1024

typedef struct {
    char term[MAX_WORD_SIZE];
    char ignore;
} term_t;

typedef struct {
    char word[MAX_WORDS_IN_TITLE][MAX_WORD_SIZE];
    int number_words;
} title_t;

term_t term[MAX_TERMS];
title_t title[MAX_TITLES];
int number_terms, number_titles;

/* Useful macros */
#define TO_OTHER_CASE(s, other_case) \
    do { \
        char *s_p_ = s; \
        while (*s_p_ != '\0') { \
            *s_p_ = other_case((int) *s_p_); \
            s_p_++; \
        } \
    } while (0)

#define TO_LOWER(s) TO_OTHER_CASE(s, tolower)

#define TO_UPPER(s) TO_OTHER_CASE(s, toupper)

#define REMOVE_ENDLINE(c, k) \
    do { \
        char *c_remove_; \
        while ((c_remove_ = strchr(c, k)) != NULL) { \
            *c_remove_ = '\0'; \
        } \
    } while (0)


/* Insert new term on the list, keeping it ordained */
void insert_term(char *word, int ignored) {
    int i, max, min, pos;

    /* Binary search for best place to insert */
    max = number_terms - 1;
    min = 0;
    while (min <= max) {
        int cmp_res;
        pos = (min + max) / 2;
        cmp_res = strcmp(word, term[pos].term);
        if (cmp_res == 0) {
            return; /* term already included */
        }
        else if (cmp_res < 0) {
            max = pos - 1;
        }
        else {
            min = pos + 1;
        }
    }
    pos = max + 1;

    /* Shift the vector and insert the term */
    for (i = number_terms; i > pos; i--) {
        term[i] = term[i - 1];
    }
    strcpy(term[pos].term, word);
    term[pos].ignore = ignored;
    number_terms++;
}


/* Insert title */
#define READ_SPACES(c) while (*c == ' ') c++
void insert_title(char *complete_title) {
    char *line = complete_title;
    title_t *t = &title[number_titles++];

    t->number_words = 0;
    READ_SPACES(line);
    while (sscanf(line, "%s", t->word[t->number_words]) == 1) {
        line += strlen(t->word[t->number_words]);
        READ_SPACES(line);
        TO_LOWER(t->word[t->number_words]);
        insert_term(t->word[t->number_words], 0);
        t->number_words++;
    }
}


/* Print term occurrences on titles */
void print_terms_on_titles() {
    int occurrence[MAX_WORDS_IN_TITLE], num_occ;
    int i, j, k, q;
    for (i = 0; i < number_terms; i++) {
        if (term[i].ignore) {
            continue;
        }
        for (j = 0; j < number_titles; j++) {
            num_occ = 0;
            for (k = 0; k < title[j].number_words; k++) {
                if (strcmp(term[i].term, title[j].word[k]) == 0) {
                    occurrence[num_occ++] = k;
                }
            }
            for (q = 0; q < num_occ; q++) {
                for (k = 0; k < title[j].number_words; k++) {
                    char *word = title[j].word[k];
                    if (k > 0) {
                        printf(" ");
                    }
                    if (k == occurrence[q]) {
                        TO_UPPER(word);
                        printf("%s", word);
                        TO_LOWER(word);
                    }
                    else {
                        printf("%s", word);
                    }
                }
                printf("\n");
            }
        }
    }
}


/* Main */
int main() {
    char line[MAX_LINE_SIZE];
    int finished_inserting_terms = 0;

    /* Insert ignorable terms */
    number_terms = 0;
    while (!finished_inserting_terms) {
        fgets(line, MAX_LINE_SIZE, stdin);
        REMOVE_ENDLINE(line, '\n');
        REMOVE_ENDLINE(line, '\r');
        if (strcmp(line, "::") == 0) {
            finished_inserting_terms = 1;                
        }
        else {
            insert_term(line, 1);
        }
    }

    /* Read titles */
    number_titles = 0;
    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL) {
        REMOVE_ENDLINE(line, '\n');
        REMOVE_ENDLINE(line, '\r');
        insert_title(line);
    }

    /* Print all terms on the titles */
    print_terms_on_titles();
    return 0;
}

