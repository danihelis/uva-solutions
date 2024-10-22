/* 327
 * Evaluating Simple C Expressions
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  200
#define MAX_VARS    26
#define ORD(c)      ((c) - 'a')

/* Main function */
int main() {
    char *p, *q, line[MAX_STRING];
    int i, total, var[MAX_VARS], used[MAX_VARS];;
    while (fgets(line, MAX_STRING, stdin) != NULL) {
        for (i = 0; i < MAX_VARS; i++) {
            var[i] = i + 1, used[i] = 0;
        }
        printf("Expression: %s", line);
        for (p = line, q = line; *p != '\n'; p++) {
            if (isalpha(*p) || *p == '+' || *p == '-') {
                *q = *p;
                q++;
            }
        }
        *q = 0;
        for (p = line, total = 0; *p != 0; p++) {
            if (isalpha(*p)) {
                if (p > line + 1 && *(p - 1) == *(p - 2)) {
                    *(p - 1) = *(p - 1) == '+' ? '[' : '{', *(p - 2) = ' ';
                }
                if (*(p + 1) != 0 && *(p + 1) == *(p + 2)) {
                    *(p + 1) = *(p + 1) == '+' ? ']' : '}', *(p + 2) = ' ';
                }
            }
        }
        for (p = line, i = 1; *p != 0; p++) {
            if (isalpha(*p)) {
                total += var[ORD(*p)] * i;
                used[ORD(*p)] = 1;
            }
            else {
                switch (*p) {
                    case '[':
                    case '{': var[ORD(*(p + 1))] += *p == '[' ? 1 : -1; break;
                    case ']':
                    case '}': var[ORD(*(p - 1))] += *p == ']' ? 1 : -1; break;
                    case '+':
                    case '-': i = *p == '+' ? 1 : -1;
                }
            }
        }
        printf("    value = %d\n", total);
        for (i = 0; i < MAX_VARS; i++) {
            if (used[i]) {
                printf("    %c = %d\n", i + 'a', var[i]);
            }
        }
    }
    return 0;
}
