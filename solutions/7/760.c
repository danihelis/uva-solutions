/* 760
 * DNA Sequencing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_INPUT   310
#define MAX_STRING  (2 * MAX_INPUT)

typedef struct {
    int index, order, rank, equal;
} suffix_t;

char string[MAX_STRING];
suffix_t suffix[MAX_STRING], *array[MAX_STRING];
int size;

/* Compare two suffixes by order */
int compare(const void *a, const void *b) {
    return (* (suffix_t **) a)->order - (* (suffix_t **) b)->order;
}

/* Create sorted array of suffixes */
void create_sorted_array() {
    int i, k;
    for (i = 0; i < size; i++) {
        suffix_t *s = &suffix[i];
        s->index = i, s->order = string[i], s->equal = 0;
        array[i] = s;
    }
    qsort(array, size, sizeof (suffix_t *), compare);
    for (k = 1; k < size; k *= 2) {
        for (array[0]->rank = 0, i = 1; i < size; i++)
            array[i]->rank = array[i - 1]->rank +
                (array[i]->order > array[i - 1]->order ? 1 : 0);
        if (array[size - 1]->rank == size - 1)
            break;
        for (i = 0; i < size; i++)
            suffix[i].order = suffix[i].rank * size +
                (i + k < size ? suffix[i + k].rank : 0);
        qsort(array, size, sizeof (suffix_t *), compare);
    }
}

/* Compute longest common prefix for each suffix */
void compute_lcp() {
    int i, equal;
    char *sp, *tp;
    for (i = 0; i < size; i++)
        array[i]->order = i;
    for (i = equal = 0; i < size; i++) {
        suffix_t *t, *s = &suffix[i];
        if (s->order == size - 1)
            continue;
        t = array[s->order + 1];
        for (sp = string + s->index + equal, tp = string + t->index + equal;
                *sp != 0 && *tp != 0 && *sp == *tp; sp++, tp++, equal++)
            ;
        s->equal = equal;
        equal = equal > 0 ? equal - 1 : 0;
    }
}

/* Find longest common substring between two strings */
void find_lcs(char *s1, char *s2) {
    char last[MAX_INPUT], common[MAX_INPUT];
    int i, div, len;
    sprintf(string, "%s0%s1", s1, s2);
    size = strlen(string);
    create_sorted_array();
    compute_lcp();
    for (i = 0, div = strlen(s1); i < size; i++)
        suffix[i].rank = i <= div ? 0 : 1;
    for (i = 2, len = 0; i < size - 1; i++) {
        suffix_t *s = array[i];
        if (s->equal > len && s->rank != array[i + 1]->rank)
            len = s->equal;
    }
    if (len == 0)
        printf("No common sequence.\n");
    else
        for (i = 2, last[0] = 0; i < size - 1; i++) {
            suffix_t *s = array[i];
            if (s->equal == len && s->rank != array[i + 1]->rank) {
                strncpy(common, string + array[i]->index, len);
                common[len] = 0;
                if (strcmp(common, last) != 0) {
                    printf("%s\n", common);
                    strcpy(last, common);
                }
            }
        }
}

/* Main function */
int main() {
    char s1[MAX_INPUT], s2[MAX_INPUT], first = 1;
    while (scanf(" %s %s", s1, s2) == 2) {
        (first ? (first = 0) : printf("\n"));
        find_lcs(s1, s2);
    }
    return EXIT_SUCCESS;
}
