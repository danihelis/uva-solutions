/* 10719
 * Quotient Polynomial
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COEF        10000
#define MAX_STRING      (12 * MAX_COEF)
#define READ(x)         (fgets(x, MAX_STRING, stdin) != NULL)

/* Main function */
int main() {
    char line[MAX_STRING];
    int coefs[MAX_COEF];

    while (READ(line)) {
        int k, r, a, i, n;
        char *s;

        assert(sscanf(line, "%d", &k) == 1);
        assert(READ(line));

        for (s = strtok(line, " \n"), n = r = 0; s != NULL;
                s = strtok(NULL, " \n"), n++) {
            assert(sscanf(s, "%d", &a) == 1);
            r = (r * k) + a;
            coefs[n] = r;
        }

        printf("q(x):");
        for (i = 0; i < n - 1; i++) {
            printf(" %d", coefs[i]);
        }
        printf("\nr = %d\n\n", coefs[n - 1]);
    }
    return EXIT_SUCCESS;
}
