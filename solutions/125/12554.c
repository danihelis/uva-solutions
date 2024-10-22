/* 12554
 * A Special "Happy Birthday" Song!!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  110
#define NUM_WORDS   16
#define MAX_PEOPLE  100

char music[NUM_WORDS][MAX_STRING] = {
    "Happy",
    "birthday",
    "to",
    "you",
    "Happy",
    "birthday",
    "to",
    "you",
    "Happy",
    "birthday",
    "to",
    "Rujia",
    "Happy",
    "birthday",
    "to",
    "you"
};

char name[MAX_PEOPLE][MAX_STRING];

/* Main function */
int main() {
    int i, k, n, all;
    assert(scanf("%d", &n) != EOF);
    for (i = 0; i < n; i++)
        assert(scanf(" %s", name[i]) != EOF);
    for (all = 0, i = 0; !all; ) 
        for (k = 0; k < NUM_WORDS; k++) {
            printf("%s: %s\n", name[i], music[k]);
            if (++i >= n)
                i = 0, all = 1;
        }  
    return EXIT_SUCCESS;
}
