/* 531
 * Compromise
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      35
#define MAX_WORDS       100
#define MAX_DICT        (2 * MAX_WORDS)

#define MAX(x,y)        ((x) > (y) ? (x) : (y))

char word[MAX_DICT][MAX_STRING], *dict[MAX_DICT];
int num_words;

char *text[2][MAX_WORDS];
int size[2];

/* Find or insert word */
char * find_or_insert(char *term) {
    int start = 0, end = num_words;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(term, dict[middle]);
        if (cmp == 0)
            return dict[middle];
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    strcpy(word[num_words], term);
    for (end = num_words; end > start; end--)
        dict[end] = dict[end - 1];
    dict[start] = word[num_words++];
    return dict[start];
}

/* Find and print largest common subsequence */
void compute_and_print_lcs() {
    char *sol[MAX_WORDS];
    int lcs[MAX_WORDS + 1][MAX_WORDS + 1];
    int i, j, n, k;
    for (j = 0; j <= size[1]; j++)
        lcs[0][j] = 0;
    for (i = 1; i <= size[0]; i++) {
        lcs[i][0] = 0;
        for (j = 1; j <= size[1]; j++) {
            lcs[i][j] = MAX(lcs[i - 1][j], lcs[i][j - 1]);
            if (text[0][i - 1] == text[1][j - 1])
                lcs[i][j] = MAX(lcs[i][j], 1 + lcs[i - 1][j - 1]);
        }
    }
    
    n = k = lcs[size[0]][size[1]], i = size[0], j = size[1]; 
    while (k > 0) {
        if (lcs[i][j] == lcs[i - 1][j])
            i--;
        else if (lcs[i][j] == lcs[i][j - 1])
            j--;
        else {
            assert(lcs[i][j] == 1 + lcs[i - 1][j - 1]);
            k--, i--, j--;
            sol[k] = text[1][j];
        }
    }
    for (k = 0; k < n; k++)
        printf("%s%c", sol[k], k == n - 1 ? '\n' : ' ');
}

/* Main function */
int main() {
    while (!feof(stdin)) {
        char term[MAX_STRING];
        int k;
        for (k = num_words = 0; k < 2; k++) {
            size[k] = 0;
            while (scanf("%s ", term) == 1 && term[0] != '#')
                text[k][size[k]++] = find_or_insert(term);
        }
        compute_and_print_lcs();
    }
    return EXIT_SUCCESS;
}
