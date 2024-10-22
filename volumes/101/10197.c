/* 10197
 * Learning Portuguese
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  40
#define MAX_SUFFIX  10

#define NUM_CONJUG  3
#define NUM_PERSONS 6


char person[NUM_PERSONS][MAX_STRING] = {"eu", "tu", "ele/ela", "n\xf3s", "v\xf3s", "eles/elas"};
char thema[NUM_CONJUG][2] = {{'a', 'a'}, {'e', 'e'}, {'i', 'e'}};
int thema_used[NUM_PERSONS] = {-1, 1, 1, 0, 0, 1};
char rule[NUM_PERSONS][10] = {"", "s", "", "mos", "is", "m"};

/* Conjugate a verb stem */
void conjugate(char *verb, int conj) {
    int i;
    for (i = 0; i < NUM_PERSONS; i++) {
        printf("%-10s%s", person[i], verb);
        if (i == 0) {
            printf("o");
        }
        else if (i == 4 && conj == 2) { /* Notable exception: iis > is */
            printf("is");
        }
        else {
            printf("%c%s", thema[conj][thema_used[i]], rule[i]);
        }
        printf("\n");
    }
}

/* Main function */
int main() {
    int test_case = 0;
    char verb[MAX_STRING], trans[MAX_STRING];
    while (scanf(" %s %s", verb, trans) != EOF) {
        char *end = verb + strlen(verb) - 1;
        int valid = 0;
        printf("%s%s (to %s)\n", (test_case == 0 ? "" : "\n"), verb, trans);
        test_case++;
        if (end > verb && *end == 'r') {
            int conj;
            end--;
            conj = (*end == 'a' ? 0 : *end == 'e' ? 1 : *end == 'i' ? 2 : -1);
            if (conj >= 0) {
                *end = 0;
                conjugate(verb, conj);
                valid = 1;
            }
        }
        if (!valid) {
            printf("Unknown conjugation\n");
        }
    }
    return 0;
}
