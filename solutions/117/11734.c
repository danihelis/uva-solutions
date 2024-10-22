/* 11734
 * Big Number of Teams will Solve This
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  50
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)

/* Main function */
int main() {
    int test, num_tests;
    char input[MAX_STRING], judge[MAX_STRING];
    assert(READ(input));
    for (num_tests = atoi(input), test = 1; test <= num_tests; test++) {
        char *i, *j, correct, equal;
        int len;
        assert(READ(input) && READ(judge));
        for (i = strtok(input, " "), j = judge, correct = equal = 1; 
                correct && i != NULL; i = strtok(NULL, " ")) {
            len = strlen(i);
            correct = strncmp(i, j, len) == 0;
            j += len;
        }
        if (correct)
            correct = *j == 0, equal = strlen(input) == strlen(judge);
        printf("Case %d: %s\n", test, !correct ? "Wrong Answer" :
                equal ? "Yes" : "Output Format Error");        
    }
    return EXIT_SUCCESS;
}
