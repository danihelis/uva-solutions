/* 10062
 * Tell me the frequencies!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE    1010
#define MAX_CHARS   128

typedef struct {
    int code, frequency;
} code_t;

/* Compare */
int compare(const void *a, const void *b) {
    code_t *x = (code_t *) a, *y = (code_t *) b;
    if (x->frequency == y->frequency)
        return y->code - x->code;
    return x->frequency - y->frequency;
}

/* Main function */
int main() {
    int first = 1;
    code_t code[MAX_CHARS];
    char line[MAX_LINE], *c;
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        int i;
        for (i = 0; i < MAX_CHARS; i++)
            code[i].code = i, code[i].frequency = 0;
        for (c = line; *c != '\n'; c++)
            code[(int) *c].frequency++;
        qsort(code, MAX_CHARS, sizeof (code_t), compare);
        (first ? first = 0 : printf("\n"));
        for (i = 0; i < MAX_CHARS; i++)
            if (code[i].frequency > 0)
                printf("%d %d\n", code[i].code, code[i].frequency);
    }
    return EXIT_SUCCESS;
}
