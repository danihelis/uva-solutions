/* 12250
 * Language Detection
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_LANGUAGE    6
#define MAX_STRING      20
#define UNKNOWN         "UNKNOWN"

char phrase[NUM_LANGUAGE][MAX_STRING] = {
    "HELLO",
    "HOLA",
    "HALLO",
    "BONJOUR",
    "CIAO",
    "ZDRAVSTVUJTE"
};
char language[NUM_LANGUAGE][MAX_STRING] = {
    "ENGLISH",
    "SPANISH",
    "GERMAN",
    "FRENCH",
    "ITALIAN",
    "RUSSIAN"
};

/* Main function */
int main() {
    int i, test = 0;
    char input[MAX_STRING];
    while (scanf(" %s", input) != EOF && input[0] != '#') {
        printf("Case %d: ", ++test);
        for (i = 0; i < NUM_LANGUAGE; i++)
            if (strcmp(input, phrase[i]) == 0) {
                printf("%s\n", language[i]);
                break;
            }
        if (i == NUM_LANGUAGE)
            printf("%s\n", UNKNOWN);
    }
    return EXIT_SUCCESS;
}
