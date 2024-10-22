/* 11221
 * Magic square palindromes.
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 10003

char input[MAX_STRING], alpha[MAX_STRING];
int size;

/* Check whether the input alpha can form a magic palindrome */
int magic_palindrome() {
    char *s, *e;
    int i, j, n = sqrt(size);
    if (n * n != size) {
        return 0;
    }
    for (s = alpha, e = alpha + size - 1; s < e; s++, e--) {
        if (*s != *e) {
            return 0;
        }
    }
    for (j = 0, s = alpha; j < n; j++) {
        for (i = 0; i < n; i++, s++) {
            if (*s != alpha[i * n + j]) {
                return 0;
            }
        }
    }
    return n;
}

/* Main function */
int main() {
    int n, test, num_tests;
    assert(scanf("%d ", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        char *c, *a;
        assert(fgets(input, MAX_STRING, stdin) != NULL);
        for (c = input, a = alpha, size = 0; *c != '\n'; c++) {
            if (isalpha(*c)) {
                *a = tolower(*c);
                a++, size++;
            }
        }
        n = magic_palindrome(); 
        printf("Case #%d:\n", test);
        (n > 0 ? printf("%d\n", n) : printf("No magic :(\n"));
    }
    return 0;
}
