/* 263
 * Number Chains
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     1010
#define MAX_STRING      15

int chain[MAX_NUMBERS];
int chain_size;

/* Compare two characters in descending order */
int compare_descending(const void *a, const void *b) {
    return *((char *) b) - *((char *) a);
}

/* Compare two characters in ascending order */
int compare_ascending(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}

/* Main function */
int main() {
    char string[MAX_STRING];
    while (scanf("%s", string) != EOF && strcmp(string, "0") != 0) {
        int repeated;
        printf("Original number was %s\n", string);
        chain_size = 0;
        do {
            int size = strlen(string), desc, asc, number, i;
            qsort(string, size, sizeof (char), compare_descending);
            sscanf(string, "%d", &desc);
            qsort(string, size, sizeof (char), compare_ascending);
            sscanf(string, "%d", &asc);
            number = desc - asc;
            printf("%d - %d = %d\n", desc, asc, number);
            for (i = 0, repeated = 0; !repeated && i < chain_size; i++) {
                repeated = (number == chain[i]);
            }
            chain[chain_size++] = number;
            sprintf(string, "%d", number);
        } while (!repeated);
        printf("Chain length %d\n\n", chain_size);
    }
    return 0;
}
