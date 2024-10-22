/* 1339
 * Ancient Cipher
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      110
#define NUM_LETTERS     26

/* Compare letters */
int compare(const void *a, const void *b) {
    return * (int *) b - * (int *) a;
}

/* Main function */
int main() {
    char message[2][MAX_STRING], *c;
    while (scanf(" %s %s", message[0], message[1]) == 2) {
        int freq[2][NUM_LETTERS], i, k, valid;
        for (k = 0; k < 2; k++) {
            memset(freq[k], 0, sizeof (freq[k]));
            for (c = message[k]; *c != 0; c++)
                freq[k][*c - 'A']++;
            qsort(freq[k], NUM_LETTERS, sizeof (int), compare);
        }
        for (valid = 1, i = 0; valid && i < NUM_LETTERS && 
                (freq[0][i] > 0 || freq[1][i] > 0); i++)
            valid = freq[0][i] == freq[1][i];
        printf("%s\n", valid ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
