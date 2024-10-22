/* 895
 * Word Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 12
#define MAX_LETTERS 26

typedef struct node_s {
    char head;
    struct node_s *child, *next;
    int count;
} node_t;

node_t root = {0, NULL, NULL, 0};

/* Add sorted word into tree */
void add_tree(node_t *node, char *word) {
    if (*word == 0)
        node->count++;
    else {
        node_t **deep = &node->child;
        while (*deep != NULL && (*deep)->head != *word)
            deep = &(*deep)->next;
        if (*deep == NULL) {
            *deep = (node_t *) malloc(sizeof (node_t));
            (*deep)->count = 0, (*deep)->child = (*deep)->next = NULL;
            (*deep)->head = *word;
            assert(islower(*word));
        }
        add_tree(*deep, word + 1);
    }
}

/* Compare letters */
int compare(const void *a, const void *b) {
    return * (char *) a -  * (char *) b;
}

/* Add word */
void add_word(char *word) {
    qsort(word, strlen(word), sizeof (char), compare);
    add_tree(&root, word);
}

/* Search for words given the letters */
int search(node_t *node, int letter[]) {
    int count = node->count;
    node_t *deep;
    for (deep = node->child; deep != NULL; deep = deep->next) {
        int index = deep->head - 'a';
        if (letter[index] > 0) {
            letter[index]--;
            count += search(deep, letter);
            letter[index]++;
        }
    }
    return count;
}

/* Free nodes */
void free_node(node_t *node) {
    node_t *deep;
    for (deep = node->child; deep != NULL; deep = deep->next) {
        free_node(deep);
        free(deep);
    }
}

/* Main function */
int main() {
    char input[MAX_STRING], symbol;
    int letter[26];
    while (scanf("%s ", input) == 1 && input[0] != '#')
        add_word(input);

    memset(letter, 0, sizeof (letter));
    while ((symbol = getchar()) != '#')
        if (islower(symbol))
            letter[symbol - 'a']++;
        else if (symbol == '\n') {
            printf("%d\n", search(&root, letter));
            memset(letter, 0, sizeof (letter));
        }
    free_node(&root);
    return EXIT_SUCCESS;
}
