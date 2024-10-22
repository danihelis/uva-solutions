/* 12504
 * Updating a Dictionary
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ENTRIES     50
#define MAX_STRING      102

typedef struct {
    char *key, *value;
} entry_t;

typedef struct {
    char input[MAX_STRING];
    entry_t entry[MAX_ENTRIES];
    int size;
} dict_t;

typedef struct {
    char *key[MAX_ENTRIES];
    int size;
} keyset_t;


/* Compare two entries by key */
int compare(const void *a, const void *b) {
    return strcmp(((entry_t *) a)->key, ((entry_t *) b)->key);
}

/* Read and sort a dictionary */
void read_dict(dict_t *dict) {
    char *c;
    assert(scanf(" %s", dict->input) != EOF);
    c = dict->input + 1, dict->size = 0; 
    while (*c != '}' && *c != 0) {
        dict->entry[dict->size].key = c;
        for (; *c != ':'; c++)
            ;
        *c = 0;
        dict->entry[dict->size++].value = ++c;
        for (; *c != ',' && *c != '}'; c++)
            ;
        *c = 0;
        c++;
    }
    qsort(dict->entry, dict->size, sizeof (entry_t), compare);
}

/* Print keyset and return its size */
int print_keyset(keyset_t *set, char symbol) {
    int i;
    if (set->size > 0) {
        printf("%c", symbol);
        for (i = 0; i < set->size; i++) {
            printf("%s%c", set->key[i], i < set->size - 1 ? ',' : '\n');
        }
    }
    return set->size;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        dict_t old, new;
        keyset_t added, removed, modified;
        int i, j, any;
        read_dict(&old);
        read_dict(&new);
        added.size = removed.size = modified.size = 0;
        i = j = any = 0;
        while (i < old.size && j < new.size) {
            int cmp = strcmp(old.entry[i].key, new.entry[j].key);
            if (cmp == 0) {
                if (strcmp(old.entry[i].value, new.entry[j].value) != 0) {
                    modified.key[modified.size++] = old.entry[i].key;
                }
                i++, j++;
            } else if (cmp < 0) {
                removed.key[removed.size++] = old.entry[i++].key;
            } else {
                added.key[added.size++] = new.entry[j++].key;
            }
        }
        for (; i < old.size; i++) {
            removed.key[removed.size++] = old.entry[i].key;
        }
        for (; j < new.size; j++) {
            added.key[added.size++] = new.entry[j].key;
        }
        any |= print_keyset(&added, '+');
        any |= print_keyset(&removed, '-');
        any |= print_keyset(&modified, '*');
        if (!any) printf("No changes\n");
        printf("\n");
    }
    return EXIT_SUCCESS;
}
