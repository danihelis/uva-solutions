/* 10361
 * Automatic Poetry
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  150
#define NUM_PARTS   5

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char line[MAX_STRING], second[MAX_STRING], *s[NUM_PARTS + 1], delim[] = "<><>\n";
    int i, k, num_tests, order[NUM_PARTS] = {0, 3, 2, 1, 4};
    assert(READ(line));
    for (num_tests = atoi(line); num_tests > 0; num_tests--) {
        assert(READ(line) && READ(second));
        for (i = 0, s[0] = line; i < NUM_PARTS; i++) {
            s[i + 1] = strchr(s[i], delim[i]);
            *(s[i + 1]) = 0;
            s[i + 1]++;
        }
        s[NUM_PARTS] = strstr(second, "...");
        *(s[NUM_PARTS]) = 0;
        for (k = 0; k < 2; k++) {
            for (i = 0; i < NUM_PARTS; i++) {
                printf("%s", k == 0 ? s[i] : i == 0 ? second : s[order[i]]);
            }
            printf("\n");
        }
    }
    return 0;
}
