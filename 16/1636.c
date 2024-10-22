/* 1636
 * Headshot
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 102

/* Main function */
int main() {
    char input[MAX_STRING];
    while (scanf(" %s", input) != EOF) {
        int i, n, shoot_good, empty, prob;
        n = strlen(input);
        for (i = shoot_good = empty = 0; i < n; i++) {
            if (input[i] == '0') {
                empty++;
                if (input[(i + 1) % n] == '0') shoot_good++;
            }
        }
        prob = shoot_good * n - empty * empty;
        printf("%s\n", prob == 0 ? "EQUAL" : prob < 0 ? "ROTATE" : "SHOOT");
    }
    return EXIT_SUCCESS;
}
