/* 10101
 * Bangla Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_GROUPS      9
#define MAX_STRING      20
#define KUTI_GROUP      4

char group[NUM_GROUPS][MAX_STRING] = {
    "", " shata", " hajar", " lakh", " kuti", 
    " shata", " hajar", " lakh", " kuti"
};
int size[NUM_GROUPS] = {0, 2, 3, 5, 7, 9, 10, 12, 14};

/* Main function */
int main() {
    int test = 0;
    char input[MAX_STRING];
    while (scanf(" %s", input) == 1) {
        int i, kuti, len = strlen(input);
        char *s = input;
        printf("%4d.", ++test);
        if (len < size[1])
            printf(" %s\n", input);
        else {
            kuti = len > size[KUTI_GROUP + 1];
            for (i = NUM_GROUPS - 1; i >= 0; i--) {
                int value = 0;
                while (len > size[i]) {
                    value = value * 10 + *s - '0';
                    s++, len--;
                }
                if (value > 0)
                    printf(" %d%s", value, group[i]);
                else if (i == KUTI_GROUP && kuti)
                    printf("%s", group[i]);
            }
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
