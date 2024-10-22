/* 417
 * Word Index
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       5
#define NUM_LETTERS 26

int table[MAX_N][NUM_LETTERS];

/* Compose index table */
void compose_table() {
    int i, j, k, index;
    for (k = 0; k < MAX_N; k++) {
        for (i = 0; i < NUM_LETTERS - k; i++) {
            index = 1 + (i == 0 ? 0 : table[k][i - 1]);
            for (j = k - 1; j >= 0; j--)
                index += table[j][NUM_LETTERS - j - 1] - 
                        table[j][i + k - j];
            table[k][i] = index;
        }
    }
}

/* Decode string using index table */
int decode(char *s) {
    int index, k, last;
    for (index = last = 0, k = strlen(s) - 1; *s != 0 && last < *s; 
            s++, k--)
        index += table[k][*s - 'a'], last = *s;
    return *s == 0 ? index : 0;
}

/* Main function */
int main() {
    char string[MAX_N + 2];
    compose_table();
    while (scanf("%s", string) != EOF)
        printf("%d\n", decode(string));
    return EXIT_SUCCESS;
}
