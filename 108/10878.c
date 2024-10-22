/* 10878
 * Decode the tape
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  20

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char line[MAX_STRING];
    assert(READ(line) && line[0] == '_');
    while (READ(line) && line[0] != '_') {
        char c, *t;
        for (c = 0, t = line + 1; *t != '|'; t++) {
            if (*t == ' ') {
                c <<= 1;
            }
            else if (*t == 'o') {
                c = (c << 1) | 0x1;
            }
        }
        printf("%c", c);
    }
    return 0;
}
