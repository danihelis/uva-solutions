/* 482
 * Permutiation Arrays
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER 10000
#define MAX_INPUT 100000

/* Main function */
int main() {
    int position[MAX_NUMBER];
    char *vector[MAX_NUMBER];
    char input[MAX_INPUT];
    int dimension = 0, index, tests;
    assert(fgets(input, MAX_INPUT, stdin) != NULL);
    tests = atoi(input);
    for (; tests > 0; tests--) {
        char *token;
        if (dimension > 0) {
            printf("\n");
        }
        assert(fgets(input, MAX_INPUT, stdin) != NULL);
        assert(input[0] == '\n');
        assert(fgets(input, MAX_INPUT, stdin) != NULL);
        dimension = 0;
        token = strtok(input, " \n");
        while (token != NULL) {
            position[dimension++] = atoi(token) - 1;
            token = strtok(NULL, " \n");
        }
        assert(fgets(input, MAX_INPUT, stdin) != NULL);
        index = 0;
        token = strtok(input, " \n");
        while (token != NULL) {
            int place = position[index++];
            assert(place < dimension);
            vector[place] = token;
            token = strtok(NULL, " \n");
        }
        for (index = 0; index < dimension; index++) {
            printf("%s\n", vector[index]);
        }
    }
    return 0;
}
