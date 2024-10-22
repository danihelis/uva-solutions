/* 11233
 * Deli Deli
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20
#define MAX_STRING  210

typedef struct {
    char singular[MAX_STRING], plural[MAX_STRING];
} word_t;

word_t word[MAX_N], *dict[MAX_N];
int size;

/* Find or insert word */
word_t *find_insert(char *singular, char *plural) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = strcmp(dict[middle]->singular, singular);
        if (comp == 0)
            return dict[middle];
        else if (comp > 0)
            end = middle;
        else
            start = middle + 1;
    }
    if (plural == NULL)
        return NULL;
    for (end = size; end > start; end--)
        dict[end] = dict[end - 1];
    strcpy(word[size].singular, singular);
    strcpy(word[size].plural, plural);
    dict[start] = &word[size++];
    return dict[start];
}

/* Print the plural form */
void print_plural(char *singular) {
    word_t *irregular = find_insert(singular, NULL);
    if (irregular != NULL)
        printf("%s\n", irregular->plural);
    else {
        char ends[] = "osx",
             vowels[] = "aeiou";
        int len = strlen(singular);
        if (len >= 2 && singular[len - 1] == 'y' && 
                strchr(vowels, singular[len - 2]) == NULL) {
            singular[len - 1] = 0;
            printf("%sies\n", singular);
        }
        else if (len >= 2 && (strcmp(singular + len - 2, "ch") == 0 ||
                strcmp(singular + len - 2, "sh") == 0))
            printf("%ses\n", singular);
        else if (strchr(ends, singular[len - 1]) != NULL)
            printf("%ses\n", singular);
        else
            printf("%ss\n", singular);
    }
}

/* Main function */
int main() {
    int num_irregulars, num_words;
    char singular[MAX_STRING], plural[MAX_STRING];
    assert(scanf("%d %d", &num_irregulars, &num_words) == 2);
    for (size = 0; num_irregulars > 0; num_irregulars--) {
        assert(scanf(" %s %s", singular, plural) == 2);
        find_insert(singular, plural);
    }
    for (; num_words > 0; num_words--) {
        assert(scanf(" %s", singular) == 1);
        print_plural(singular);
    }
    return EXIT_SUCCESS;
}
