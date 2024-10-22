/* 195
 * Anagram
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  10000

char input[MAX_STRING], used[MAX_STRING], permutation[MAX_STRING];
int n;

/* Compare two chars */
int compare(const void *a, const void *b) {
    char ca = *((char *) a), cb = *((char *) b);
    char la = tolower(ca), lb = tolower(cb);
    return la == lb ? ca - cb : la - lb;
}

/* Generate permutations */
void generate_permutations(int index) {
    if (index >= n) {
        printf("%s\n", permutation);
    }
    else {
        int i;
        char last;
        for (i = 0, last = 0; i < n; i++) {
            if (!used[i] && input[i] != last) {
                permutation[index] = input[i];
                used[i] = 1;
                generate_permutations(index + 1);
                used[i] = 0;
                last = input[i];
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf(" %s", input) != EOF);
        n = strlen(input);
        qsort(input, n, sizeof (char), compare);
        memset(used, 0, n * sizeof (char));
        permutation[n] = 0;
        generate_permutations(0);
    }
    return 0;
}
