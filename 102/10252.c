/* 10252
 * Common Permutation
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1002
#define MAX_CHARS   ('z' - 'a' + 1)
#define MIN(x, y)   ((x) < (y) ? (x) : (y))
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)

/* Main function */
int main() {
    int ca[MAX_CHARS], cb[MAX_CHARS];
    char a[MAX_STRING], b[MAX_STRING];
    int i;
    while (READ(a) && READ(b)) {
        for (i = 0; i < 2; i++) {
            char *p = (i ? b : a);
            int *c = (i ? cb : ca);
            memset(c, 0, sizeof (int) * MAX_CHARS);
            for (; *p != '\n'; p++) {
                c[*p - 'a']++;
            }
        }
        for (i = 0; i < MAX_CHARS; i++) {
            int total = MIN(ca[i], cb[i]);
            for (; total > 0; total--) {
                printf("%c", 'a' + i);
            }
        }
        printf("\n");
    }
    return 0;
}
