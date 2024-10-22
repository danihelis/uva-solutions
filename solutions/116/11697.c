/* 11697
 * Playfair Cipher
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     5
#define MAX_STRING  1005
#define MAX_ALPHA   26

char matrix[MAX_DIM][MAX_DIM];

/* Set matrix from phrase */
void set_matrix(char *phrase) {
    char used[MAX_ALPHA], *p;
    int i, j, k;
    memset(used, 0, MAX_ALPHA);
    used['q' - 'a'] = 1;
    for (p = phrase, i = j = 0; *p != 0; p++)
        if (islower(*p) && !used[*p - 'a']) {
            used[*p - 'a'] = 1;
            matrix[i][j] = *p;
            if (++j >= MAX_DIM)
                i++, j = 0;
        }
    for (k = 0; k < MAX_ALPHA; k++)
        if (!used[k]) {
            matrix[i][j] = 'a' + k;
            if (++j >= MAX_DIM)
                i++, j = 0;
        }
}

/* Print code from digraph */
void print_code(char s1, char s2) {
    int r1, r2, c1, c2, i, j;
    r1 = r2 = c1 = c2 = -1;
    for (i = 0; (r1 == -1 || r2 == -1) && i < MAX_DIM; i++)
        for (j = 0; (r1 == -1 || r2 == -1) && j < MAX_DIM; j++) {
            if (matrix[i][j] == s1)
                r1 = i, c1 = j;
            if (matrix[i][j] == s2)
                r2 = i, c2 = j;
        }
    if (r1 == r2) 
        c1 = (c1 + 1) % MAX_DIM, c2 = (c2 + 1) % MAX_DIM;
    else if (c1 == c2)
        r1 = (r1 + 1) % MAX_DIM, r2 = (r2 + 1) % MAX_DIM;
    else {
        int swap = c1;
        c1 = c2;
        c2 = swap;
    }    
    printf("%c%c", toupper(matrix[r1][c1]), toupper(matrix[r2][c2]));
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char phrase[MAX_STRING], message[MAX_STRING], *c1, *c2, equal;
        assert(scanf(" %[^\n] %[^\n]", phrase, message) != EOF);
        set_matrix(phrase);
        c1 = message; 
        while (*c1 != 0) {
            while (*c1 == ' ')
                c1++;
            c2 = c1 + 1;
            while (*c2 == ' ')
                c2++;
            equal = (*c1 == *c2 || *c2 == 0);
            print_code(*c1, equal ? 'x' : *c2);
            c1 = c2 + (equal ? 0 : 1);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
