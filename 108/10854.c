/* 10854
 * Number of Paths
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  12
#define MAX_STACK   100000
    
char command[MAX_STRING];

/* Count if executions recursivelly */
long count_exec() {
    long total = 0, current = 1;
    while (scanf(" %s", command) != EOF && 
            strncmp(command, "END", 3) != 0) {
        if (command[0] == 'I')
            current *= count_exec();
        else if (strncmp(command, "EL", 2) == 0) {
            total += current;
            current = 1;
        }
    }
    total += current;
    return total;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        printf("%ld\n", count_exec());
    }

    return EXIT_SUCCESS;
}
