/* 11151
 * Longest Palindrome
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     1000
#define MAX_STRING  (MAX_DIM + 2)

#define MAX(x, y)   ((x) > (y) ? (x) : (y))

/* Determine longest palindrome subsequence */
int longest_palindrome_subsequence(char *string) {
    int i, j, k, dim;
    int table[MAX_STRING][MAX_STRING];
    for (i = 0, dim = strlen(string) - 1; i < dim; i++) {
        table[i][i] = 1, table[i + 1][i] = 0;
    }
    for (k = 1; k < dim; k++) {
        for (i = 0, j = k; j < dim; i++, j++) {
            table[i][j] = MAX(table[i + 1][j], table[i][j - 1]);
            if (string[i] == string[j]) {
                table[i][j] = MAX(table[i + 1][j - 1] + 2, table[i][j]);
            }
        }
    }
    return (dim > 0 ? table[0][dim - 1] : 0);
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char string[MAX_STRING];
    int num_tests;
    assert(READ(string));
    for (num_tests = atoi(string); num_tests > 0; num_tests--) {
        assert(READ(string));
        printf("%d\n", longest_palindrome_subsequence(string));
    }
    return 0;
}
