/* 13181
 * Sleeping in hostels
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       500000
#define MAX_STR     (MAX_N + 2)
#define PILGRAM     'X'

/* Main function */
int main() {
    char row[MAX_STR];
    while (scanf(" %s", row) == 1) {
        int i, distance, last, highest;
        char *c;
        for (i = highest = 0, last = -1, c = row; *c != 0; i++, c++) {
            if (*c == PILGRAM) {
                if (last == -1) distance = i - 1;
                else distance = (i - last - 2) / 2;
                if (distance > highest) highest = distance;
                last = i;
            }
        }
        distance = i - last - 2;
        if (distance > highest) highest = distance;
        printf("%d\n", highest);
    }
    return EXIT_SUCCESS;
}
