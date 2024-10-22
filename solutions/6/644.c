/* 644
 * Immediate Decodability
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  15
#define MAX_CODES   10

typedef char string_t[MAX_STRING];
string_t code[MAX_CODES];

/* Main function */
int main() {
    int j, i, comp, set = 0;
    while (scanf(" %s", code[0]) != EOF) {
        i = 0, comp = 1;
        while (code[i][0] != '9') { 
            for (j = 0; comp && j < i; j++) {
                char *c1, *c2, prefix = 1;
                for (c1 = code[j], c2 = code[i]; prefix && *c1 != 0 && *c2 != 0; c1++, c2++) {
                    prefix = *c1 == *c2;
                }
                comp = !prefix;
            }
            i++;
            assert(scanf(" %s", code[i]) != EOF);
        }
        printf("Set %d is %simmediately decodable\n", ++set, (comp ? "" : "not "));
    }
    return 0;
}
