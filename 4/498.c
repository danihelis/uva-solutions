/* 498
 * Polly the Polynomial
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX_STRING  (MAX_N * 10)
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
#define SEP         " \t\n"

/* Main function */
int main() {
    char line[MAX_STRING], *t;
    while (READ(line)) {
        int coef[MAX_N], n, first;
        for (t = strtok(line, SEP), n = 0; t != NULL; 
                t = strtok(NULL, SEP), n++)
            coef[n] = atoi(t);
        assert(READ(line));
        for (t = strtok(line, SEP), first = 1; t != NULL; 
                t = strtok(NULL, SEP), first = 0) {
            long i, f, x, v;
            for (i = n - 1, x = atoi(t), v = 0, f = 1; i >= 0; i--, f *= x)
                v += f * coef[i];
            printf("%s%ld", first ? "" : " ", v);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
