/* 10929
 * You can say 11
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1010
#define BASE        11

/* Determine whether a bigint is multiple of BASE */
int is_multiple(char *bigint) {
    int last;
    for (last = 0; isdigit(*bigint); bigint++) {
        last = (last * 10 + *bigint - '0') % BASE;
    }
    return last == 0;
}

/* Main function */
int main() {
    char bigint[MAX_STRING];
    while (scanf(" %s", bigint) != EOF && strcmp(bigint, "0") != 0) {
        printf("%s is %sa multiple of %d.\n", bigint, is_multiple(bigint) ? "" : "not ", BASE);
    }
    return 0;
}
