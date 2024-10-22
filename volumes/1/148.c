/* 148
 * Anagram checker
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  50
#define MAX_KEYS    2001
#define MAX_LETTERS 26

typedef char string_t[MAX_STRING];

string_t key[MAX_KEYS];
string_t input;
int selected[MAX_STRING], input_set[MAX_STRING];
int letter[MAX_LETTERS];
int num_keys, num_selected, num_input_set;

/* Compare two ints */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compare two strings */
int compare(const void *a, const void *b) {
    return strcmp(*((string_t *) a), *((string_t *) b));
}

/* Find all possible permutations with the given letters */
void find_permutation(int k, int total) {
    if (total == 0) {
        if (num_selected > 0) {
            if (num_selected == num_input_set) {
                int i, equal = 1;
                for (i = 0; equal && i < num_selected && i < num_input_set; i++) {
                    equal = (selected[i] == input_set[i]);
                }
                if (equal) {
                    return;
                }
            }
            printf("%s =", input);
            for (k = 0; k < num_selected; k++) {
                printf(" %s", key[selected[k]]);
            }
            printf("\n");
        }
        return;
    }
    else {
        for (; k < num_keys; k++) {
            char *p, inc, use;
            for (p = key[k], use = 1, inc = 0; use && *p != 0; p++, inc++) {
                use = (--letter[*p - 'A'] >= 0);
            }
            if (use) {
                selected[num_selected++] = k;
                find_permutation(k + 1, total - inc);
                num_selected--;
            }
            for (--p; p >= key[k]; p--) {
                letter[*p - 'A']++;
            }
        }
    }
}

/* Main function */
int main() {
    num_keys = 0;
    while (scanf(" %s", key[num_keys]) != EOF && key[num_keys][0] != '#') {
        num_keys++;
    }
    while (scanf(" %[^\n]", input) != EOF && input[0] != '#') {
        int total;
        char *p, *t;
        string_t token, *f;
        num_input_set = 0;
        memset(letter, 0, sizeof (int) * MAX_LETTERS);
        for (p = input, t = token, total = 0; *p != 0; p++) {
            if (isalpha(*p)) {
                letter[*p - 'A']++;
                total++;
                *t = *p;
                t++;
            }
            else if (t > token) {
                *t = 0;
                f = bsearch(&token, key, num_keys, sizeof (string_t), compare);
                input_set[num_input_set++] = (f == NULL ? -1 : f - key);
                t = token;
            }
        }
        if (t > token) {
            *t = 0;
            f = bsearch(&token, key, num_keys, sizeof (string_t), compare);
            input_set[num_input_set++] = (f == NULL ? -1 : f - key);
        }
        qsort(input_set, num_input_set, sizeof (int), compare_int);
        num_selected = 0;
        find_permutation(0, total);
    }
    return 0;
}
