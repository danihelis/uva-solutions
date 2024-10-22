/* 10508
 * Word Morphing
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CHARS   1000000

typedef char string_t[MAX_CHARS];

string_t first, last;
int change[MAX_CHARS], pos[MAX_CHARS];

/* Main function */
int main() {
    int num_chars;
    while (scanf("%*d %d", &num_chars) != EOF) {
        int i, k, index;
        assert(scanf(" %s %s", first, last) != EOF);
        memset(change, 0, num_chars * sizeof (int));
        for (i = 1; i < num_chars; i++) {
            string_t current;
            char *c, *d;
            assert(scanf(" %s", current) != EOF);
            for (index = 0, c = current, d = last; *c != 0; c++, d++) {
                index += (*c == *d ? 1 : 0);
            }
            for (k = 0, c = current, d = last; *c != 0; c++, d++, k++) {
                if (*c == *d && (change[k] == 0 || change[k] > index)) {
                    change[k] = index;
                }
            }
        }
        for (i = 0; i < num_chars; i++) {
            pos[(change[i] + num_chars - 1) % num_chars] = i;
        }
        printf("%s\n", first);
        for (i = 0; i < num_chars; i++) {
            first[pos[i]] = last[pos[i]];
            printf("%s\n", first);
        }
    }
    return 0;
}
