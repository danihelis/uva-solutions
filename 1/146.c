/* 146
 * ID Codes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  60

int compare(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}

/* Main function */
int main() {
    char string[MAX_STRING];
    while (scanf(" %s", string) != EOF && string[0] != '#') {
        char *c, *change, *minor;
        int size;
        for (c = string, change = NULL, size = 0; *c != 0; c++, size++) {
            if (*c < *(c + 1)) {
                change = c;
                minor = c + 1;
            }
            else if (change != NULL && *c > *change && *c < *minor) {
                minor = c;
            }
        }
        if (change == NULL) {
            printf("No Successor\n");
        }
        else {
            char tmp = *minor;
            *minor = *change;
            *change = tmp;
            qsort(change + 1, size - (change - string) - 1, sizeof (char), compare);
            printf("%s\n", string);
        }
    }
    return 0;
}
