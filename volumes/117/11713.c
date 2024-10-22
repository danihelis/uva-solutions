/* 11713
 * Abstract Names
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    30
#define NUM_VOWELS  5

char vowel[] = "aeiou";

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        char name[2][MAX_SIZE], *c;
        int i;
        assert(scanf(" %s %s", name[0], name[1]) == 2);
        if (strlen(name[0]) == strlen(name[1]))
            for (i = 0; i < 2; i++)
                for (c = name[i]; *c != 0; c++)
                    if (strchr(vowel, *c) != NULL)
                        *c = '*';
        printf("%s\n", strcmp(name[0], name[1]) == 0 ? "Yes" : "No");
    }
    return EXIT_SUCCESS;
}
