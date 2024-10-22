/* 11062
 * Andy's Second Dictionary
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH  1000
#define MAX_N       500

typedef char string_t[MAX_LENGTH];

string_t word[MAX_N], *dict[MAX_N];
int size;

/* Insert if not present in the dictionary */
void insert(char *new) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(new, *dict[middle]);
        if (cmp == 0)
            return;
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    for (end = size; end > start; end--)
        dict[end] = dict[end - 1];
    strcpy(word[size], new);
    dict[start] = &word[size++];
}

/* Main function */
int main() {
    string_t current;
    char symbol;
    int i, len = 0;
    size = 0;
    while ((symbol = getchar()) != EOF) {
        if (isalpha(symbol) || symbol == '-')
            current[len++] = tolower(symbol);
        else if (len > 0) {
            if (current[len - 1] == '-')
                len--;
            else {
                current[len] = 0;
                insert(current);
                len = 0;
            }
        }
    }
    if (len > 0) {
        current[len] = 0;
        insert(current);
    }
    for (i = 0; i < size; i++)
        puts(*dict[i]);
    return EXIT_SUCCESS;
}
