/* 902
 * Password Search
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SUBSTRING   11
#define MAX_INPUT       1100000
#define MAX_HASHTABLE   999917
#define NUM_CHARS       26

typedef char substring_t[MAX_SUBSTRING];

typedef struct node_s {
    substring_t content;
    int count;
    struct node_s *next, *next_global;
} node_t, *node_p;

node_p hashtable[MAX_HASHTABLE], max_count, last_node;

/* Hash value */
int hash_value(char *s) {
    long hash;
    for (hash = 0; *s != 0; s++) {
        hash = (hash * NUM_CHARS + *s - 'a' + 1) % MAX_HASHTABLE;
    }
    return (int) hash;
}

/* Insert into hashtable */
void insert(char *s) {
    int hash = hash_value(s);
    node_p *n = &hashtable[hash];
    while ((*n) != NULL && strcmp((*n)->content, s) != 0) {
        n = &((*n)->next);
    }
    if ((*n) == NULL) {
        (*n) = (node_p) malloc(sizeof (node_t));
        (*n)->count = 1;
        strcpy((*n)->content, s);
        (*n)->next = NULL;
        (*n)->next_global = last_node;
        last_node = *n;
    }
    else {
        (*n)->count++;
    }
    if (max_count == NULL || (*n)->count > max_count->count) {
        max_count = *n;
    }
}

/* Erase all memory allocated */
void erase_all() {
    while (last_node != NULL) {
        node_p p = last_node->next_global;
        free(last_node);
        last_node = p;
    }
    memset(hashtable, 0, MAX_HASHTABLE * sizeof (node_p));
    last_node = NULL, max_count = NULL;
}

/* Main function */
int main() {
    char line[MAX_INPUT];
    int size;
    last_node = NULL;
    while (scanf("%d", &size) != EOF) {
        char *c;
        assert(scanf(" %s", line) != EOF);
        erase_all();
        for (c = line + size - 1; *c != 0; c++) {
            char backup = *(c + 1);
            *(c + 1) = 0;
            insert(c - size + 1);
            *(c + 1) = backup;
        }
        printf("%s\n", max_count->content);
    }
    return 0;
}
